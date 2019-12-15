#ifndef SCREENSHOTMAINWINDOW_H
#define SCREENSHOTMAINWINDOW_H

#include <QMainWindow>
#include "screenshot.h"
#include <QHotkey>
#include <QKeySequence>
#include <QMessageBox>
#include <QSystemTrayIcon>

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
    QSystemTrayIcon *trayIcon;
};

#endif // SCREENSHOTMAINWINDOW_H
