#include "fillspace.h"

void FillSpace::setPixelColor(QPoint point)
{
    painter->drawPoint(point);
}

bool FillSpace::isPixelInImage(QPoint point)
{
    return (point.x()<image->size().rwidth()
            && point.y()<image->size().rheight()
            && point.x()>=0
            && point.y()>=0);
}

void FillSpace::choosePixelToColoring(QPoint point)
{
    if(isPixelInImage(point))
        if(image->pixelColor(point) == color)
        {
            setPixelColor(point);
            points << point;
        }
}

void FillSpace::fillSpace()
{
    points.clear();
    QPoint lastPoint;

    choosePixelToColoring(QPoint(x,y));
    while(!points.isEmpty())
    {
        lastPoint = points.takeLast();
        choosePixelToColoring(QPoint(lastPoint.x()+1,lastPoint.y()));
        choosePixelToColoring(QPoint(lastPoint.x()-1,lastPoint.y()));
        choosePixelToColoring(QPoint(lastPoint.x(),lastPoint.y()+1));
        choosePixelToColoring(QPoint(lastPoint.x(),lastPoint.y()-1));
    }
}

FillSpace::FillSpace(QImage *image, QPainter *painter, QColor color, int x, int y)
{
    this->image = image;
    this->painter = painter;
    this->color = color;
    this->x = x;
    this->y = y;

    fillSpace();
}
