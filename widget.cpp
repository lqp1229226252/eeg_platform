#include "widget.h"
ComboBox::ComboBox(QWidget *parent):QWidget (parent)
{

   this->label.setAlignment(Qt::AlignCenter);
//   this->vbox.addWidget(label,0,Qt::AlignCenter)
   this->vbox.addWidget(self.combobox)
   this->combobox.currentIndexChanged.connect(self.solt)
   this->setSize()
}



//Widget::Widget(QWidget *parent)
//    : QWidget(parent)
//{
//}

//Widget::~Widget()
//{

//}

