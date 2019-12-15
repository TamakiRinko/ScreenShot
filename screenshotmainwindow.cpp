#include "screenshotmainwindow.h"
#include "ui_screenshotmainwindow.h"

ScreenShotMainWindow::ScreenShotMainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ScreenShotMainWindow){
    ui->setupUi(this);
    ScreenShot* screenShot = new ScreenShot();
//    ui->ScreenShotLayout->addWidget(screenShot);
}

ScreenShotMainWindow::~ScreenShotMainWindow(){
    delete ui;
}

