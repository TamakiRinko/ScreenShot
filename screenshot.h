#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QDesktopWidget>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QPoint>
#include <QPen>
#include <QDebug>
#include <QFileDialog>
#include <iostream>
#include "sizeinfo.h"
using namespace std;

enum OperationType{
    NONE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT, CONTAINS, OUTSIDE,
    LEFT, RIGHT, TOP, BOTTOM
};

class ScreenShot : public QWidget{
    Q_OBJECT
public:
    explicit ScreenShot(QWidget *parent = nullptr);
private:
    QPixmap* backgroundOrigin;                              //原色背景图
    QPixmap* backgroundGray;                                //灰色背景图
    SizeInfo* curSizeInfo;                                  //矩形窗口大小信息

    QPoint* mousePos;                                       //鼠标位置
    int curMode;                                            //当前状态
    QPoint startPoint;                                      //矩形框开始位置
    QPoint endPoint;                                        //矩形框结束位置
    QRect cutRect;                                          //裁剪矩形框
    OperationType curOperationType;                         //当前操作类型
    QPoint* pressPoint;                                     //按下的按键
    bool isSaving;                                          //是否正在保存，正在保存则不画直线

    void generateGrayBackground();                          //生成灰色背景图
    QPixmap* getBackgroundOrigin();                         //获得原色背景图
    void generateCutRect();                                 //获得裁剪矩形框
    OperationType generateOperation(QPoint point);          //根据位置获得操作
    bool isOnPoint(QPoint point1, QPoint point2);           //在point1位置上
    bool isOnLine(int l, int pos);                          //在l线上

protected:
    void paintEvent(QPaintEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
};

#endif // SCREENSHOT_H
