#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


enum Mode{
    DRAW,
    DRAW_LINE,
    DRAW_RECT,
    DRAW_ELLIPSE
};

enum Shape{
    NORMAL,
    EQUAL
};

enum Brush{
    NONE,
    FULL
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QColor penColor;
    QColor brushColor;
    QImage image;

    void setDraw();
    void setDrawLine();
    void setDrawRect();
    void setDrawEllipse();
    void setShapeNormal();
    void setShapeEqual();
    void setBrushNone();
    void setBrushFull();
private:
    Ui::Widget *ui;
    QImage tempImage;
    int lastX;
    int lastY;
    int actualX;
    int actualY;
    Mode mode;
    Shape shape;
    Brush brush;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent * event);
    QRect GetRect(int x, int y);
    QImage *GetImage();
    bool IsTempImage();
};

#endif // WIDGET_H
