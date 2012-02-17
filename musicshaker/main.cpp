#include <QtGui/QApplication>
#include <QtDBus/QtDBus>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include "qmlapplicationviewer.h"
#include "musicshaker.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    MusicShaker *shaker = new MusicShaker();
    qWarning() << shaker;

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("shaker", shaker);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/musicshaker/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
