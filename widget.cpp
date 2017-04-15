#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include "QMouseEvent"
#include "QPaintEvent"
#include "QPainter"
#include "QImage"
#include <QRect>
#include <cmath>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    image(800,600, QImage::Format_RGB32),
    tempImage(800,600, QImage::Format_RGB32)
{
    penColor = QColor(Qt::black);
    brushColor = QColor(Qt::white);
    ui->setupUi(this);
    image.fill(Qt::white);
    mode = DRAW;
    shape = NORMAL;
    brush = NONE;
    scale = 1.0;
    setMinimumSize(800*scale,600*scale);
    fileName = "";
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setNewImage(int width, int height)
{
    setMinimumSize(width*scale,height*scale);
    image = QImage(width,height, QImage::Format_RGB32);
    image.fill(Qt::white);
    tempImage = image;
    fileName = "";
}

void Widget::loadImage(QString file)
{
    image.load(file);
    tempImage = image;
    setMinimumSize(image.size().rwidth()*scale,image.size().rheight()*scale);
    fileName = file;
}

void Widget::saveImage()
{
    image.save(fileName);
}

QString Widget::getFileName()
{
    return fileName;
}

void Widget::saveImage(QString file)
{
    image.save(file);
    fileName = file;
}

QColor Widget::getPenColor()
{
    return penColor;
}

void Widget::setPenColor(QColor color)
{
    penColor = color;
}

QColor Widget::getBrushColor()
{
    return brushColor;
}

void Widget::setBrushColor(QColor color)
{
    brushColor = color;
}

void Widget::mousePressEvent(QMouseEvent * e)
{
    lastX = e->x()/scale;
    lastY = e->y()/scale;

}

QRect Widget::GetRect(int x,int y)
{
    QRect rect = QRect();
    if(shape == EQUAL)
        rect.setRect(lastX,lastY,x-lastX,x-lastX);
    else
        rect.setCoords(lastX,lastY,x,y);
    return rect;
}

QImage * Widget::GetImage()
{
    if(IsTempImage())
    {
        tempImage = image;
        return &tempImage;
    }
    else
        return &image;
}

bool Widget::IsTempImage()
{
    return (mode == DRAW_LINE || mode == DRAW_RECT || mode == DRAW_ELLIPSE);
}

void Widget::mouseMoveEvent(QMouseEvent * e)
{
    QPainter p(GetImage());
    p.setPen(penColor);
    if (brush == FULL)
        p.setBrush(brushColor);

    switch (mode) {
    case DRAW:
        p.drawLine(e->x()/scale,e->y()/scale,lastX,lastY);
        lastX = e->x()/scale;
        lastY = e->y()/scale;
        break;
    case DRAW_LINE:
        p.drawLine(e->x()/scale,e->y()/scale,lastX,lastY);
        break;
    case DRAW_RECT:
        p.drawRect(GetRect(e->x()/scale,e->y()/scale));
        actualX = e->x()/scale;
        actualY = e->y()/scale;
        break;
    case DRAW_ELLIPSE:
        p.drawEllipse(GetRect(e->x()/scale,e->y()/scale));
        actualX = e->x()/scale;
        actualY = e->y()/scale;
        break;
    }

    update();
}

void Widget::mouseReleaseEvent(QMouseEvent * e)
{
    QPainter p(&image);
    p.setPen(penColor);
    if (brush == FULL)
        p.setBrush(brushColor);

    switch (mode) {
    case DRAW:
        break;
    case DRAW_LINE:
        p.drawLine(e->x()/scale,e->y()/scale,lastX,lastY);
        break;
    case DRAW_RECT:
        p.drawRect(GetRect(e->x()/scale,e->y()/scale));
        break;
    case DRAW_ELLIPSE:
        p.drawEllipse(GetRect(e->x()/scale,e->y()/scale));
        break;
    }

    lastX = e->x()/scale;
    lastY = e->y()/scale;
    update();
}


void Widget::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.scale(scale,scale);
    if(IsTempImage())
        p.drawImage(0,0,tempImage);
    else
        p.drawImage(0,0,image);
}

void Widget::setDraw()
{
    mode = DRAW;
}

void Widget::setDrawLine()
{
    mode = DRAW_LINE;
}

void Widget::setDrawRect()
{
    mode = DRAW_RECT;
}

void Widget::setDrawEllipse()
{
    mode = DRAW_ELLIPSE;
}

void Widget::setShapeNormal()
{
    shape = NORMAL;
}

void Widget::setShapeEqual()
{
    shape = EQUAL;
}

void Widget::setBrushNone()
{
    brush = NONE;
}

void Widget::setBrushFull()
{
    brush = FULL;
}

bool Widget::zoomIn()
{
    if(scale+0.1 <= 3.0)
    {
        scale+=0.1;
        setMinimumSize(image.size().rwidth()*scale,image.size().rheight()*scale);
        update();
    }

    if(scale+0.1 <= 3.0)
        return true;
    else
        return false;
}

bool Widget::zoomOut()
{
    if(scale-0.1 >= 0.1)
    {
        scale-=0.1;
        setMinimumSize(image.size().rwidth()*scale,image.size().rheight()*scale);
        update();
    }

    if(scale-0.1 >= 0.1)
        return true;
    else
        return false;
}

void Widget::zoomReset()
{
    scale = 1.0;
    setMinimumSize(image.size().rwidth()*scale,image.size().rheight()*scale);
    update();
}
