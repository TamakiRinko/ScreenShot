#ifndef SCREENSHOTMAINWINDOW_H
#define SCREENSHOTMAINWINDOW_H

#include <QMainWindow>
#include "screenshot.h"

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
};

#endif // SCREENSHOTMAINWINDOW_H
