#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>


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

    void setNewImage(int width, int height);
    void loadImage(QString file);
    void saveImage(QString file);
    void saveImage();
    QString getFileName();

    QColor getPenColor();
    void setPenColor(QColor color);
    QColor getBrushColor();
    void setBrushColor(QColor color);

    void setDraw();
    void setDrawLine();
    void setDrawRect();
    void setDrawEllipse();

    void setShapeNormal();
    void setShapeEqual();

    void setBrushNone();
    void setBrushFull();

    bool zoomIn();
    bool zoomOut();
    void zoomReset();

    void setMouseLabel(QLabel *label);
private:
    Ui::Widget *ui;
    QString fileName;
    QImage image;
    QImage tempImage;
    QColor penColor;
    QColor brushColor;
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
    qreal scale;
    QLabel * mouseLabel;
    void changeMouseLabel(int x, int y);
};

#endif // WIDGET_H
