#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widget.h>
#include <QPushButton>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *colorButton;

public slots:
    void setColor();

private slots:
    void on_actionDraw_triggered();

    void on_actionDraw_Line_triggered();

    void on_actionDraw_Rect_triggered();

    void on_actionDraw_Ellipse_triggered();

    void on_actionNormal_triggered();

    void on_actionEqual_triggered();

private:
    Ui::MainWindow *ui;
    Widget *mywidget;
};

#endif // MAINWINDOW_H
