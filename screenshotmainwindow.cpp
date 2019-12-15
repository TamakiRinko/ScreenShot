#include "screenshotmainwindow.h"
#include "ui_screenshotmainwindow.h"


ScreenShotMainWindow::ScreenShotMainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ScreenShotMainWindow){
    ui->setupUi(this);

    //设置托盘图标
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/Picture/截屏.png");
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("ScreenShot");
    trayIcon->show();

    //设置托盘操作
    iconMenu = new QMenu(this);
    quitAction = new QAction("退出程序", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    iconMenu->addAction(quitAction);
    trayIcon->setContextMenu(iconMenu);

    QHotkey* hotkey = new QHotkey(QKeySequence("Ctrl+Shift+A"), true);          //截图全局快捷键
    QObject::connect(hotkey, &QHotkey::activated, this, [&](){
        ScreenShot* screenShot = new ScreenShot();
    });

}

ScreenShotMainWindow::~ScreenShotMainWindow(){
    delete ui;
}


void ScreenShotMainWindow::closeEvent(QCloseEvent* e){
    if(trayIcon->isVisible()){
        hide(); //隐藏窗口
        e->ignore(); //忽略事件
    }
}
