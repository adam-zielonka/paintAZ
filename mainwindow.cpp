#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QColorDialog>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mywidget = new Widget(this);
    setCentralWidget(mywidget);
    colorButton = new QPushButton(this);
    colorButton->setStyleSheet("background-color: "+mywidget->color.name()+";");
    ui->toolBar->addWidget(colorButton);
    connect(colorButton,SIGNAL(clicked()),this,SLOT(setColor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setColor()
{
    mywidget->color = QColorDialog::getColor();
    colorButton->setStyleSheet("background-color: "+mywidget->color.name()+";");
}

void MainWindow::on_actionDraw_triggered()
{
    mywidget->setDraw();
}

void MainWindow::on_actionDraw_Line_triggered()
{
    mywidget->setDrawLine();
}

void MainWindow::on_actionDraw_Rect_triggered()
{
    mywidget->setDrawRect();
}

void MainWindow::on_actionDraw_Ellipse_triggered()
{
    mywidget->setDrawEllipse();
}

void MainWindow::on_actionNormal_triggered()
{
    mywidget->setShapeNormal();
}

void MainWindow::on_actionEqual_triggered()
{
    mywidget->setShapeEqual();
}
