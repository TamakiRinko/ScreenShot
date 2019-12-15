#include "sizeinfo.h"
#include "ui_sizeinfo.h"

SizeInfo::SizeInfo(QWidget *parent): QWidget(parent), ui(new Ui::SizeInfo){
    ui->setupUi(this);
    setFixedSize(100, 20);
    blackBackground = new QPixmap(this->width(), this->height());
    blackBackground->fill(QColor(0, 0, 0, 220));
    show();
}

SizeInfo::~SizeInfo(){
    delete ui;
}

void SizeInfo::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(rect(),*blackBackground);
    painter.setPen(QPen(QColor(Qt::white)));
    painter.drawText(rect(), Qt::AlignCenter, sizeInfo);                //居中写大小
}

void SizeInfo::changePos(QPoint point, int xMax, int yMax) {
    int x = point.x() + width() > xMax ? xMax - width() : point.x();
    int y = point.y() + height() > yMax ? yMax - height() : point.y();
    move(x, y);
    update();
}

void SizeInfo::changeSize(QSize size) {
    sizeInfo = QString("%1 × %2").arg(size.width()).arg(size.height());
    update();
}
