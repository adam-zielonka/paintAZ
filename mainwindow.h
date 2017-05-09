#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widget.h>
#include <newfiledialog.h>
#include <textdialog.h>
#include <QPushButton>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <QFileDialog>
#include <QScrollArea>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *brushColorButton;
    QPushButton *penColorButton;
    NewFileDialog * newFile;
    QScrollArea * scrollArea;
    QLabel * mouseLabel;
    void updateWindowTitle();

public slots:
    void setPenColor();
    void setBrushColor();

private slots:
    void on_actionDraw_triggered();

    void on_actionDraw_Line_triggered();

    void on_actionDraw_Rect_triggered();

    void on_actionDraw_Ellipse_triggered();

    void on_actionNormal_triggered();

    void on_actionEqual_triggered();

    void on_actionNone_triggered();

    void on_actionFull_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionZoom_to_Actual_Size_triggered();

    void on_actionText_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::MainWindow *ui;
    Widget *mywidget;
};

#endif // MAINWINDOW_H
