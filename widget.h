#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QComboBox"
#include "QLabel"
#include "QVBoxLayout"
class ComboBox: public QWidget
{
    Q_OBJECT
public:
    ComboBox(QWidget *parent=NULL);
    void setlabel(QString Text);
    void setItems(QStringList list);
    void setFontSize(QFont font);
    void setSize(int w=100,int h=80);


signals:
    void currentIndexChanged(int index);

public slots:
    void slot(int index);

private:
    QLabel label;
    QComboBox combobox;
    QVBoxLayout vbox();

};
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = NULL);
    ~Widget();
};

#endif // WIDGET_H
