#include "screenshot.h"

ScreenShot::ScreenShot(QWidget *parent) : QWidget(parent){
    backgroundGray = nullptr;
    backgroundOrigin = nullptr;
    curSizeInfo = nullptr;
    mousePos = new QPoint(0, 0);
    curMode = 0;
    curOperationType = NONE;
    pressPoint = nullptr;
    isSaving = false;

    setMouseTracking(true);                              //实时跟踪

    generateGrayBackground();
    showFullScreen();
//    Qt::WindowFlags flags = windowFlags();
//    flags |= Qt::WindowStaysOnTopHint;
//    setWindowFlags(flags);
//    show();
}

void ScreenShot::generateGrayBackground(){
    QPixmap* originScreen = getBackgroundOrigin();
    backgroundGray = new QPixmap(*originScreen);
    QPixmap grayBackground(originScreen->width(), originScreen->height());  //背景
    grayBackground.fill((QColor(0, 0, 0, 128)));                            //变为灰色
    QPainter p(backgroundGray);
    p.drawPixmap(0, 0, grayBackground);
    backgroundGray->save("/home/rinko/test/testscreenshot.jpg");
}

QPixmap* ScreenShot::getBackgroundOrigin(){
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect desktopRect = QRect(QApplication::desktop()->pos(), QApplication::desktop()->size());
    backgroundOrigin = new QPixmap(QPixmap(screen->grabWindow(
                                               0, desktopRect.x(), desktopRect.y(),
                                               desktopRect.width(), desktopRect.height())));
    return backgroundOrigin;
}

void ScreenShot::generateCutRect(){
    int xMin = startPoint.x() > endPoint.x() ? endPoint.x() : startPoint.x();
    int xMax = startPoint.x() < endPoint.x() ? endPoint.x() : startPoint.x();
    int yMin = startPoint.y() > endPoint.y() ? endPoint.y() : startPoint.y();
    int yMax = startPoint.y() < endPoint.y() ? endPoint.y() : startPoint.y();
    cutRect = QRect(QPoint(xMin, yMin), QPoint(xMax, yMax));
}

OperationType ScreenShot::generateOperation(QPoint point){
    if(isOnPoint(cutRect.topLeft(), point)){            //左上角
        curOperationType = TOPLEFT;
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }else if(isOnPoint(cutRect.topRight(), point)){     //右上角
        curOperationType = TOPRIGHT;
        setCursor(QCursor(Qt::SizeBDiagCursor));
    }else if(isOnPoint(cutRect.bottomLeft(), point)){   //左下角
        curOperationType = BOTTOMLEFT;
        setCursor(QCursor(Qt::SizeBDiagCursor));
    }else if(isOnPoint(cutRect.bottomRight(), point)){  //右下角
        curOperationType = BOTTOMRIGHT;
        setCursor(QCursor(Qt::SizeFDiagCursor));
    }else if(isOnLine(cutRect.top(), point.y())){       //上
        curOperationType = TOP;
        setCursor(QCursor(Qt::SizeVerCursor));
    }else if(isOnLine(cutRect.bottom(), point.y())){    //下
        curOperationType = BOTTOM;
        setCursor(QCursor(Qt::SizeVerCursor));
    }else if(isOnLine(cutRect.left(), point.x())){      //左
        curOperationType = LEFT;
        setCursor(QCursor(Qt::SizeHorCursor));
    }else if(isOnLine(cutRect.right(), point.x())){     //右
        curOperationType = RIGHT;
        setCursor(QCursor(Qt::SizeHorCursor));
    }else if(cutRect.contains(point)){                  //内部
        curOperationType = CONTAINS;
        setCursor(QCursor(Qt::SizeAllCursor));
    }else{
        curOperationType = OUTSIDE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
    return curOperationType;
}

bool ScreenShot::isOnPoint(QPoint point1, QPoint point2){
    int x1 = point1.x();
    int y1 = point1.y();
    int x2 = point2.x();
    int y2 = point2.y();

    for(int j = -5; j <= 5; ++j){
        for(int k = -5; k <= 5; ++k){
            int x = x1 + j;
            int y = y1 + k;
            if(x2 == x && y2 == y){
                return true;
            }
        }
    }

    return false;
}

bool ScreenShot::isOnLine(int l, int pos){
    for(int j = -5; j <= 5; ++j){
        if(l + j == pos){
            return true;
        }
    }
    return false;
}

void ScreenShot::paintEvent(QPaintEvent*){
    QPainter painter(this);
    if(backgroundGray != nullptr){
        painter.drawPixmap(backgroundGray->rect(), *backgroundGray, QRect());           //灰色背景
    }
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    if(curMode == 0 && !isSaving){                                                      //基准线
        painter.drawLine(0, mousePos->y(), backgroundGray->size().width(), mousePos->y());
        painter.drawLine(mousePos->x(), 0, mousePos->x(), backgroundGray->size().height());
    }else{
        painter.drawPixmap(QPoint(cutRect.x(),cutRect.y()), *backgroundOrigin, cutRect);//原色背景
        painter.drawRect(cutRect);                                                      //红色边框
        if(curSizeInfo != nullptr){
            curSizeInfo->changePos(cutRect.bottomRight(), width(), height());           //在右下端画出图片大小
            curSizeInfo->changeSize(cutRect.size());
        }
    }

}

/**
 * @brief ScreenShot::keyPressEvent
 * @param e
 * 按Esc关闭截图
 */
void ScreenShot::keyPressEvent(QKeyEvent* e){
    if(e->key() == Qt::Key_Escape){                         //Esc退出
        if(curMode == 2){
            curMode = 0;
            this->setCursor(QCursor(Qt::ArrowCursor));
            curSizeInfo->close();
            update();
        }else{
            close();
        }
    }else if(e->key() == Qt::Key_Return){                   //Return结束，保存图片
        isSaving = true;
        update();
        if(curSizeInfo != nullptr){                         //??????
            curSizeInfo->close();
        }
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "newPic", tr("Image (*.jpg)"));
        if(fileName == ""){
            isSaving = false;
            curSizeInfo = new SizeInfo(this);
            return;
        }
        if(curMode == 0){                                   //未选取，全部保存
            backgroundOrigin->save(fileName);
        }else if(curMode == 2){
            QPixmap pixMap(cutRect.width(), cutRect.height());
            QPainter painter(&pixMap);
            painter.drawPixmap(QPoint(0, 0), *backgroundOrigin, cutRect);
            pixMap.save(fileName);
        }
        close();
    }
}

void ScreenShot::mousePressEvent(QMouseEvent* e){
    if(curMode == 0 && e->button() == Qt::LeftButton){
        curMode = 1;
        startPoint = e->pos();
        cutRect = QRect(startPoint, startPoint);
        curSizeInfo = new SizeInfo(this);
    }else if(curMode == 2){                                 //已选中，进行操作
        pressPoint = new QPoint(e->pos());
    }
//    update();
}

void ScreenShot::mouseReleaseEvent(QMouseEvent* e){
    if(curMode == 1 && e->button() == Qt::LeftButton){
        curMode = 2;
        endPoint = e->pos();
        generateCutRect();
    }else if(curMode == 2 && e->button() == Qt::RightButton         //右键点击外侧，取消当前选择
             && generateOperation(e->pos()) == OUTSIDE){
        curMode = 0;
        this->setCursor(QCursor(Qt::ArrowCursor));
        curSizeInfo->close();
    }

    pressPoint = nullptr;
    curOperationType = NONE;
    update();
}

void ScreenShot::mouseMoveEvent(QMouseEvent* e){
    mousePos->setX(e->pos().x());
    mousePos->setY(e->pos().y());
    if(curMode == 1){
        endPoint = e->pos();
        generateCutRect();
    }else if(curMode == 2){
        if(pressPoint != nullptr){
            int x = e->pos().x();
            int y = e->pos().y();
            int xMin = cutRect.topLeft().x();
            int yMin = cutRect.topLeft().y();
            int xMax = cutRect.bottomRight().x();
            int yMax = cutRect.bottomRight().y();
            switch(curOperationType){
                case CONTAINS:{
                    int dx = e->pos().x() - pressPoint->x();
                    int dy = e->pos().y() - pressPoint->y();
                    cutRect.moveTo(cutRect.topLeft().x() + dx, cutRect.topLeft().y() + dy);
                    pressPoint = new QPoint(e->pos());
                    break;
                }
                case TOPLEFT:{
                    if(x < xMax && y < yMax){
                        cutRect.setTopLeft(e->pos());
                    }
                    break;
                }
                case TOPRIGHT:{
                    if(x > xMin && y < yMax){
                        cutRect.setTopRight(e->pos());
                    }
                    break;
                }
                case BOTTOMLEFT:{
                    if(x < xMax && y > yMin){
                        cutRect.setBottomLeft(e->pos());
                    }
                    break;
                }
                case BOTTOMRIGHT:{
                    if(x > xMin && y > yMin){
                        cutRect.setBottomRight(e->pos());
                    }
                    break;
                }
                case TOP:{
                    if(y < yMax){
                        cutRect.setTop(y);
                    }
                    break;
                }
                case BOTTOM:{
                    if(y > yMin){
                        cutRect.setBottom(y);
                    }
                    break;
                }
                case LEFT:{
                    if(x < xMax){
                        cutRect.setLeft(x);
                    }
                    break;
                }
                case RIGHT:{
                    if(x > xMin){
                        cutRect.setRight(x);
                    }
                    break;
                }
                default: break;
            }
        }else{
            generateOperation(e->pos());
        }
    }
    update();
}
