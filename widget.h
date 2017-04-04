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

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    QImage image;
    QImage tempImage;
    int lastX;
    int lastY;
    int actualX;
    int actualY;
    Mode mode;
    Shape shape;
    QColor color;

    void setDraw();
    void setDrawLine();
    void setDrawRect();
    void setDrawEllipse();
    void setShapeNormal();
    void setShapeEqual();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
