#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <cmath>
#include <QList>
#include <QTextEdit>
#include <QSpinBox>
#include <QFontComboBox>
#include <QLineEdit>
#include <QPolygon>
#include <QPoint>
#include <QDebug>

enum Mode{
    DRAW,
    DRAW_LINE,
    DRAW_RECT,
    DRAW_ROUND_RECT,
    DRAW_ELLIPSE,
    FILL,
    TEXT
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

    void setDrawSize(QSpinBox * drawSizeSpinBox);

    void setDraw();
    void setDrawLine();
    void setDrawRect();
    void setDrawEllipse();
    void setDrawRoundRect();
    void setFill();

    void setShapeNormal();
    void setShapeEqual();

    void setBrushNone();
    void setBrushFull();

    bool zoomIn();
    bool zoomOut();
    void zoomReset();

    void setMouseLabel(QLabel *label);

    void setUndoImage(QAction * undo);
    void setRedoImage(QAction * redo);
    void undoImage();
    void redoImage();

    void setPaintDefault();
    void setPaintText();
    void setTextEdit(QLineEdit * textEdit,QSpinBox * fontSizeSpinBox,QFontComboBox * fontComboBox);
    bool setBoldFont();
    bool setItalicsFont();
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
    QAction * undo;
    QAction * redo;
    QList<QImage> imageListUndo;
    QList<QImage> imageListRedo;
    bool undoAgain;
    bool redoAgain;
    QLineEdit * textEdit;
    QSpinBox * fontSizeSpinBox;
    QFontComboBox * fontComboBox;
    bool boldFont;
    bool italicsFont;
    QSpinBox * drawSizeSpinBox;
    int getEndOfLine(QColor color, int x, int y);
    int getBeginOfLine(QColor color, int x, int y);
    int getYEndOfLine(QColor color, int x, int y);
    int getYBeginOfLine(QColor color, int x, int y);
    void fillColor(QPainter * painter, QColor color, int x, int y);
    int counterFill;
};

#endif // WIDGET_H
