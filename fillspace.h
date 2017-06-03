#ifndef FILLSPACE_H
#define FILLSPACE_H

#include<QPainter>
#include<QList>

class FillSpace
{
private:
    QList<QPoint> points;
    QImage * image;
    QPainter * painter;
    QColor color;
    int x, y;
    void setPixelColor(QPoint point);
    bool isPixelInImage(QPoint point);
    void choosePixelToColoring(QPoint point);
    void fillSpace();

public:
    FillSpace(QImage *image, QPainter * painter, QColor color, int x, int y);
};

#endif // FILLSPACE_H
