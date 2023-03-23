#ifndef SOMECLASS_H
#define SOMECLASS_H

#include <QObject>
#include<QDebug>

class SomeClass : public QObject
{
    Q_OBJECT
public:
    explicit SomeClass(QObject *parent = nullptr);

signals:

public slots:
 void callSlot();

};

#endif // SOMECLASS_H
