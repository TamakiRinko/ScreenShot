#include "screenshotmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    ScreenShotMainWindow w;
    w.show();
//    w.close();
//    a.quit();
//    return 0;
    return a.exec();
}
