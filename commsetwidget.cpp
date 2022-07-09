#include "commsetwidget.h"
#include "ui_commsetwidget.h"
#include "QFontDatabase"
#include "QDebug"
#include "QtSerialPort/QSerialPortInfo"
#include "QLineEdit"
#include <QPalette>
#include "QMessageBox"
CommSetWidget::CommSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommSetWidget)
{
    ui->setupUi(this);
    this->serial=new QSerialPort();
    this->pause_flag=false;
    setFont();
    setUI();
    on_serial_detect_clicked();
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(serial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(dealError(QSerialPort::SerialPortError)));
}

CommSetWidget::~CommSetWidget()
{
    delete ui;
}
void CommSetWidget::setFont()
{
    int id=QFontDatabase::addApplicationFont(":/fontawesome-webfont.ttf");
    QString fontname=QFontDatabase::applicationFontFamilies(id).at(0);
    font.setFamily(fontname);
    ui->stop->setFont(font);
    ui->start->setFont(font);
    ui->pause->setFont(font);
    ui->direct_light->setFont(font);
}
void CommSetWidget::setUI()
{

    ui->direct_light->setText(QChar(0xf111));
    this->setLightColor(Qt::red);
    ui->start->setText(QChar(0xf04b));
    ui->pause->setText(QChar(0xf04c));
    ui->stop->setText(QChar(0xf04d));

    ui->start->setStyleSheet("QPushButton { background-color: transparent;border:none; }");
    ui->pause->setStyleSheet("QPushButton { background-color: transparent;border:none; }");
    ui->stop->setStyleSheet("QPushButton { background-color: transparent;border:none; }");

    QStringList bound_rates={"1000000","9600","57600","115200"};
    ui->bound_rate->addItems(bound_rates);
    ui->bound_rate->setEditable(true);
}

void CommSetWidget::setLightColor(Qt::GlobalColor color)
{
    QPalette pe;
    pe.setColor(QPalette::Background,Qt::black);
    pe.setColor(QPalette::WindowText,color);
    ui->direct_light->setPalette(pe);
}
void CommSetWidget::write(QByteArray buffer)
{
    this->serial->write(buffer);
}
void CommSetWidget::messageBox(QString str)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText(str);
    msgBox.exec();
}
void CommSetWidget::on_start_clicked()
{
    QString portname=ui->serial->currentText();
    int bound_rate=ui->bound_rate->currentText().toInt();
    serial->setPortName(portname);
    serial->setBaudRate(bound_rate);
    if(!serial->isOpen())
    {
        if(serial->open(QIODevice::ReadWrite))
        {
            this->pause_flag=false;
            this->setLightColor(Qt::yellow);
        }
        else {
            this->messageBox("串口打开失败");
        }
    }
    else {
        this->messageBox("串口已经打开");
    }

}

void CommSetWidget::on_pause_clicked()
{
    if(serial->isOpen())
    {
       pause_flag=true;
    }
    else {
        this->messageBox("串口没有打开");
    }
}

void CommSetWidget::on_stop_clicked()
{
    if(serial->isOpen())
    {
        this->serial->close();
        this->setLightColor(Qt::red);
        this->pause_flag=false;
    }
    else {
      this->messageBox("串口没有打开");
    }
}

void CommSetWidget::on_serial_detect_clicked()
{
    //获取全部串口信息
    QList<QSerialPortInfo> infos=QSerialPortInfo::availablePorts();
    //将检测的串口名字插入serialnames
    for(int i=0;i<infos.size();i++)
    {
       this->serialnames.append(infos[i].portName());
    }
    //将检测的串口显示到窗口
    ui->serial->addItems(this->serialnames);
}
void CommSetWidget::readData()
{
    this->setLightColor(Qt::green);
    if(!this->pause_flag)
    {
        //开始读取数据
        QByteArray data=this->serial->readAll();
        qDebug()<<data;
    }
}

void CommSetWidget::dealError(QSerialPort::SerialPortError error)
{
    if(error==QSerialPort::ResourceError)
    {
        this->setLightColor(Qt::red);
        this->messageBox("设备已经断开");
    }
}
