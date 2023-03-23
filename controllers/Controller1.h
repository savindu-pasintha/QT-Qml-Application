#ifndef CONTROLLER1_H
#define CONTROLLER1_H

#include <QObject>
#include <QDebug>

class Controller1:public QObject
{
     Q_OBJECT
public:
    explicit Controller1(QObject *parent = 0);
    Controller1();


    Q_INVOKABLE void method1();
    Q_INVOKABLE void method2(int x,int y);

signals:

public slots:
    void cppSlot(const QString &msg);
};

#endif // CONTROLLER1_H
