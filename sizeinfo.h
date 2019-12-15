#ifndef SIZEINFO_H
#define SIZEINFO_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class SizeInfo;
}

class SizeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SizeInfo(QWidget *parent = nullptr);
    ~SizeInfo();

private:
    Ui::SizeInfo *ui;
    QPixmap* blackBackground;
    QString sizeInfo;

protected:
    void paintEvent(QPaintEvent *);

public:
    void changePos(QPoint point, int xMax, int yMax);
    void changeSize(QSize size);
};

#endif // SIZEINFO_H
