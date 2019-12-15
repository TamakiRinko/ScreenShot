#include "screenshotmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);             //没有可见窗口不会关闭
    ScreenShotMainWindow w;
    return a.exec();
}
