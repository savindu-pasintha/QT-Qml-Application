#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<controllers/Controller1.h>
#include<QQuickView>
#include<QObject>
#include<QQuickItem>
#include<controllers/someclass.h>
#include<QQmlContext>

//https://www.youtube.com/watch?v=ragZPvRe6Pk



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    SomeClass myClass;

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/views/main.qml");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    QQmlContext *rootContext = engine.rootContext();
    rootContext->setContextProperty("classA",&myClass);

    return app.exec();
}

//  const QUrl url(u"qrc:/Qt_Quick_Application/main.qml"_qs);
