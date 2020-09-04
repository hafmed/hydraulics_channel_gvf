#include "hydraulics-channel-gvf.h"
#include <QApplication>

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QApplication::setGraphicsSystem("raster");
#endif
    QApplication::setApplicationName("hydraulics-channel-gvf");
    QApplication::setOrganizationName("HAFIANE Mohamed");
    QApplication a(argc, argv);
    hydraulics_channel_gvf w;
    QPixmap pixmap = QPixmap (":/icons/hydraulics-channel-gvf.ico");
    w.setWindowIcon(QIcon(pixmap));
    w.show();

    return a.exec();
}
