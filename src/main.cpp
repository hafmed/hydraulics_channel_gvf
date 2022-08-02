#include "hydraulics-channel-gvf.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("hydraulics-channel-gvf");
    QApplication::setOrganizationName("HAFIANE Mohamed");
    QApplication app(argc, argv);
    //-----
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    // Setup and load translator for localization
    //-----
    QTranslator translator;
    //QString locale = QLocale::system().name();
    QString locale = QString(QLocale::system().name()).left(2);
    if (locale.length() < 2) locale = "en";
    //qDebug()<<"locale="<<QLocale::system().name();
    if (locale!="fr")
    {
        locale="en";
        if(translator.load(QString(":/translations/qt_") + locale))
            app.installTranslator(&translator);
    }
    //-----
    hydraulics_channel_gvf w;
    QPixmap pixmap = QPixmap (":/icons/hydraulics-channel-gvf.ico");
    w.setWindowIcon(QIcon(pixmap));
    w.show();
    return app.exec();
}
