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
    color = QColor(Qt::black);
    ui->setupUi(this);
    image.fill(Qt::white);
    mode = DRAW;
    shape = NORMAL;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent * e)
{
    lastX = e->x();
    lastY = e->y();

}

void Widget::mouseMoveEvent(QMouseEvent * e)
{
    switch (mode) {
    case DRAW:
    {
        QPainter p(&image);
        p.setPen(color);
        p.drawLine(e->x(),e->y(),lastX,lastY);
        lastX = e->x();
        lastY = e->y();
        update();
        break;
    }
    case DRAW_LINE:
    {
        tempImage = image;
        QPainter p(&tempImage);
        p.setPen(color);
        p.drawLine(e->x(),e->y(),lastX,lastY);
        update();
        break;
    }
    case DRAW_RECT:
    {
        tempImage = image;
        QPainter p(&tempImage);
        p.setPen(color);
        QRect rect = QRect();
        if(shape == EQUAL)
            rect.setRect(lastX,lastY,e->x()-lastX,e->x()-lastX);
        else
            rect.setCoords(lastX,lastY,e->x(),e->y());
        p.drawRect(rect);
        actualX = e->x();
        actualY = e->y();
        update();
        break;
    }
    case DRAW_ELLIPSE:
    {
        tempImage = image;
        QPainter p(&tempImage);
        p.setPen(color);
        QRect rect = QRect();
        if(shape == EQUAL)
            rect.setRect(lastX,lastY,e->x()-lastX,e->x()-lastX);
        else
            rect.setCoords(lastX,lastY,e->x(),e->y());
        p.drawEllipse(rect);
        actualX = e->x();
        actualY = e->y();
        update();
        break;
    }
    }
}

void Widget::mouseReleaseEvent(QMouseEvent * e)
{
    switch (mode) {
    case DRAW:
    {
        break;
    }
    case DRAW_LINE:
    {
        QPainter p(&image);
        p.setPen(color);
        p.drawLine(e->x(),e->y(),lastX,lastY);
        lastX = e->x();
        lastY = e->y();
        update();
        break;
    }
    case DRAW_RECT:
    {
        QPainter p(&image);
        p.setPen(color);
        QRect rect = QRect();
        if(shape == EQUAL)
            rect.setRect(lastX,lastY,e->x()-lastX,e->x()-lastX);
        else
            rect.setCoords(lastX,lastY,e->x(),e->y());
        p.drawRect(rect);
        p.setPen(color);
        lastX = e->x();
        lastY = e->y();
        update();
        break;
    }
    case DRAW_ELLIPSE:
    {
        QPainter p(&image);
        p.setPen(color);
        QRect rect = QRect();
        if(shape == EQUAL)
            rect.setRect(lastX,lastY,e->x()-lastX,e->x()-lastX);
        else
            rect.setCoords(lastX,lastY,e->x(),e->y());
        p.drawEllipse(rect);
        lastX = e->x();
        lastY = e->y();
        update();
        break;
    }
    }
}


void Widget::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.drawImage(0,0,image);
    if(mode == DRAW_LINE || mode == DRAW_RECT || mode == DRAW_ELLIPSE)
        p.drawImage(0,0,tempImage);
}


void Widget::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_P:
        mode = DRAW;
        break;
    case Qt::Key_L:
        mode = DRAW_LINE;
        break;
    case Qt::Key_R:
        mode = DRAW_RECT;
        break;
    case Qt::Key_E:
        mode = DRAW_ELLIPSE;
        break;
    case Qt::Key_Shift:
        shape = EQUAL;
        switch (mode) {
        case DRAW_RECT:
        {
            tempImage = image;
            QPainter p(&tempImage);
            p.setPen(color);
            QRect rect = QRect();
            if(shape == EQUAL)
                rect.setRect(lastX,lastY,actualX-lastX,actualX-lastX);
            else
                rect.setCoords(lastX,lastY,actualX,actualY);
            p.drawRect(rect);
            update();
            break;
        }
        case DRAW_ELLIPSE:
        {
            tempImage = image;
            QPainter p(&tempImage);
            p.setPen(color);
            QRect rect = QRect();
            if(shape == EQUAL)
                rect.setRect(lastX,lastY,actualX-lastX,actualX-lastX);
            else
                rect.setCoords(lastX,lastY,actualX,actualY);
            p.drawEllipse(rect);
            update();
            break;
        }
        }
        break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        shape = NORMAL;
        switch (mode) {
        case DRAW_RECT:
        {
            tempImage = image;
            QPainter p(&tempImage);
            p.setPen(color);
            QRect rect = QRect();
            if(shape == EQUAL)
                rect.setRect(lastX,lastY,actualX-lastX,actualX-lastX);
            else
                rect.setCoords(lastX,lastY,actualX,actualY);
            p.drawRect(rect);
            update();
            break;
        }
        case DRAW_ELLIPSE:
        {
            tempImage = image;
            QPainter p(&tempImage);
            p.setPen(color);
            QRect rect = QRect();
            if(shape == EQUAL)
                rect.setRect(lastX,lastY,actualX-lastX,actualX-lastX);
            else
                rect.setCoords(lastX,lastY,actualX,actualY);
            p.drawEllipse(rect);
            update();
            break;
        }
        }
        break;
    }
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
