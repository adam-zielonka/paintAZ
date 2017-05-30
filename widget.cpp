#include "widget.h"
#include "ui_widget.h"

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
    setMouseTracking(true);
    imageListUndo << image;
    boldFont = false;
    italicsFont = false;
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
    imageListUndo.clear();
    imageListUndo << image;
    imageListRedo.clear();
}

void Widget::loadImage(QString file)
{
    image.load(file);
    tempImage = image;
    setMinimumSize(image.size().rwidth()*scale,image.size().rheight()*scale);
    fileName = file;
    imageListUndo.clear();
    imageListUndo << image;
    imageListRedo.clear();
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

void Widget::setDrawSize(QSpinBox * drawSizeSpinBox)
{
    this->drawSizeSpinBox = drawSizeSpinBox;
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
    return (mode == DRAW_LINE ||
            mode == DRAW_RECT ||
            mode == DRAW_ROUND_RECT ||
            mode == DRAW_ELLIPSE);
}

void Widget::changeMouseLabel(int x, int y)
{
    if ((image.size().rwidth() >= x/scale)
            && (image.size().rheight() >= y/scale)
            && (0 <= x)
            && (0 <= y)
            )
        mouseLabel->setText("x: "+QString::number((int)(x/scale))+" y: "+QString::number((int)(y/scale)));
}

void Widget::fillColor(QPainter *painter, QColor color, int x, int y)
{
    if(x>image.size().rwidth()-1 || y>image.size().rheight()-1 || x<0 || y<0)
        return;
    if(image.pixelColor(x,y) == color)
    {
        painter->drawPoint(x,y);
        update();
        fillColor(painter,color,x+1,y);
        fillColor(painter,color,x,y+1);
        fillColor(painter,color,x-1,y);
        fillColor(painter,color,x,y-1);
    }
}

void Widget::mouseMoveEvent(QMouseEvent * e)
{
    if(undoAgain)
    {
        imageListUndo << image;
        undoAgain = false;
    }

    changeMouseLabel(e->x(),e->y());
    if(e->buttons() == Qt::LeftButton)
    {
        QPainter p(GetImage());
        p.setPen(QPen(penColor, drawSizeSpinBox->value()));
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
        case DRAW_ROUND_RECT:
            p.drawRoundRect(GetRect(e->x()/scale,e->y()/scale));
            actualX = e->x()/scale;
            actualY = e->y()/scale;
            break;
        case DRAW_ELLIPSE:
            p.drawEllipse(GetRect(e->x()/scale,e->y()/scale));
            actualX = e->x()/scale;
            actualY = e->y()/scale;
            break;
        case FILL:
            break;
        case TEXT:
            break;
        }

        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent * e)
{
    QPainter p(&image);
    p.setPen(QPen(penColor, drawSizeSpinBox->value()));
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
    case DRAW_ROUND_RECT:
        p.drawRoundRect(GetRect(e->x()/scale,e->y()/scale));
        break;
    case DRAW_ELLIPSE:
        p.drawEllipse(GetRect(e->x()/scale,e->y()/scale));
        break;
    case FILL:
        if(image.pixelColor(e->x()/scale,e->y()/scale) != penColor)
            fillColor(&p,image.pixelColor(e->x()/scale,e->y()/scale),e->x()/scale,e->y()/scale);
        break;
    case TEXT:
        QFont font = QFont(fontComboBox->currentFont());
        font.setPointSize(fontSizeSpinBox->value());
        font.setBold(boldFont);
        font.setItalic(italicsFont);
        p.setFont(font);
        p.drawText(e->x()/scale,e->y()/scale,textEdit->text());
        break;
    }

    lastX = e->x()/scale;
    lastY = e->y()/scale;

    imageListUndo << image;
    undo->setEnabled(true);
    undoAgain = false;

    imageListRedo.clear();
    redo->setEnabled(false);
    redoAgain = false;

    update();
}


void Widget::paintEvent(QPaintEvent * event)
{
    event->accept();
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

void Widget::setDrawRoundRect()
{
    mode = DRAW_ROUND_RECT;
}

void Widget::setFill()
{
    mode = FILL;
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

void Widget::setMouseLabel(QLabel *label)
{
    mouseLabel = label;
}

void Widget::setUndoImage(QAction *undo)
{
    this->undo = undo;
}

void Widget::setRedoImage(QAction *redo)
{
    this->redo = redo;
}

void Widget::undoImage()
{
    if(!undoAgain)
    {
        imageListRedo << imageListUndo.takeLast();
    }
    undoAgain = true;
    redoAgain = false;
    image = tempImage = imageListUndo.takeLast();
    if(!imageListUndo.isEmpty())
        undo->setEnabled(true);
    else
    {
        undo->setEnabled(false);
        imageListUndo << image;
    }

    redo->setEnabled(true);
    imageListRedo << image;

    update();
}

void Widget::redoImage()
{
    if(!redoAgain)
    {
        if(imageListUndo.size() != 1)
            imageListUndo << imageListRedo.takeLast();
        else
            imageListRedo.takeLast();
    }
    redoAgain = true;
    undoAgain = false;
    image = tempImage = imageListRedo.takeLast();
    if(!imageListRedo.isEmpty())
        redo->setEnabled(true);
    else
        redo->setEnabled(false);

    undo->setEnabled(true);
    imageListUndo << image;

    update();
}

void Widget::setPaintDefault()
{
    mode = DRAW;
}

void Widget::setPaintText()
{
    mode = TEXT;
}

void Widget::setTextEdit(QLineEdit * textEdit,QSpinBox * fontSizeSpinBox,QFontComboBox * fontComboBox)
{
    this->textEdit = textEdit;
    this->fontSizeSpinBox = fontSizeSpinBox;
    this->fontComboBox = fontComboBox;
}

bool Widget::setBoldFont()
{
    boldFont = !boldFont;
    return boldFont;
}

bool Widget::setItalicsFont()
{
    italicsFont = !italicsFont;
    return italicsFont;
}
