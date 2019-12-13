#include "smartcontrolmainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QScreen>
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/images/fonts/arlrdbd.ttf");

    a.setWindowIcon(QIcon(":/images/icons/oneicon.png"));

    SmartControlMainWindow w;

    w.show();

    return a.exec();
}
