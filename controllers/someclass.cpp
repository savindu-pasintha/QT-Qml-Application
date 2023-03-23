#include "someclass.h"

SomeClass::SomeClass(QObject *parent)
    : QObject{parent}
{

}

void SomeClass::callSlot()
{
  qDebug()<<"void SomeClass::callSlot()";
}
