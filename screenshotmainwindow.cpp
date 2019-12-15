#include "screenshotmainwindow.h"
#include "ui_screenshotmainwindow.h"


ScreenShotMainWindow::ScreenShotMainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ScreenShotMainWindow){
    ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/icon.png");
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("a trayicon example");
    trayIcon->show(); //必须调用，否则托盘图标不显示

    QHotkey* hotkey = new QHotkey(QKeySequence("Ctrl+Shift+A"), true);          //截图全局快捷键
    QObject::connect(hotkey,&QHotkey::activated,qApp,[&](){
        ScreenShot* screenShot = new ScreenShot();
    });

}

ScreenShotMainWindow::~ScreenShotMainWindow(){
    delete ui;
}

