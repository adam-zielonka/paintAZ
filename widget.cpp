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
    setMinimumSize(800,600);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setNewImage(int width, int height)
{
    setMinimumSize(width,height);
    image = QImage(width,height, QImage::Format_RGB32);
    image.fill(Qt::white);
}

void Widget::loadImage(QString file)
{
    image.load(file);
    setMinimumSize(image.size());
}

void Widget::saveImage(QString file)
{
    image.save(file);
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
    lastX = e->x();
    lastY = e->y();

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
        p.drawLine(e->x(),e->y(),lastX,lastY);
        lastX = e->x();
        lastY = e->y();
        break;
    case DRAW_LINE:
        p.drawLine(e->x(),e->y(),lastX,lastY);
        break;
    case DRAW_RECT:
        p.drawRect(GetRect(e->x(),e->y()));
        actualX = e->x();
        actualY = e->y();
        break;
    case DRAW_ELLIPSE:
        p.drawEllipse(GetRect(e->x(),e->y()));
        actualX = e->x();
        actualY = e->y();
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
        p.drawLine(e->x(),e->y(),lastX,lastY);
        break;
    case DRAW_RECT:
        p.drawRect(GetRect(e->x(),e->y()));
        break;
    case DRAW_ELLIPSE:
        p.drawEllipse(GetRect(e->x(),e->y()));
        break;
    }

    lastX = e->x();
    lastY = e->y();
    update();
}


void Widget::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
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
