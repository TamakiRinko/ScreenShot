#ifndef SCREENSHOTMAINWINDOW_H
#define SCREENSHOTMAINWINDOW_H

#include <QMainWindow>
#include "screenshot.h"
#include <QHotkey>
#include <QKeySequence>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>

namespace Ui {
class ScreenShotMainWindow;
}

class ScreenShotMainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit ScreenShotMainWindow(QWidget *parent = nullptr);
    ~ScreenShotMainWindow();

private:
    Ui::ScreenShotMainWindow *ui;
    QSystemTrayIcon* trayIcon;                      //托盘图标
    QMenu* iconMenu;                                //托盘菜单
    QAction* quitAction;                            //退出操作

    void closeEvent(QCloseEvent* e);
};

#endif // SCREENSHOTMAINWINDOW_H
