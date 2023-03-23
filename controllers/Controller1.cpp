#include "Controller1.h"

Controller1::Controller1(QObject *parent):QObject(parent)
{

}

Controller1::Controller1()
{
   qDebug()<<"contructor ()";
}

void Controller1::method1()
{
   qDebug()<<"method1()";
}

void Controller1::method2(int x, int y)
{
    qDebug()<<"method2(x,y)"<<x<<" - "<<y;
}

void Controller1::cppSlot(const QString &msg)
{
    qDebug() << "Called the C++ slot with message:" << msg;
}
