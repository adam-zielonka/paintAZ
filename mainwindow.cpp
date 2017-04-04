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

    penColorButton = new QPushButton(this);
    penColorButton->setStyleSheet("background-color: "+mywidget->penColor.name()+";");
    ui->toolBar->addWidget(penColorButton);
    connect(penColorButton,SIGNAL(clicked()),this,SLOT(setPenColor()));

    brushColorButton = new QPushButton(this);
    brushColorButton->setStyleSheet("background-color: "+mywidget->brushColor.name()+";");
    ui->toolBar->addWidget(brushColorButton);
    connect(brushColorButton,SIGNAL(clicked()),this,SLOT(setBrushColor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPenColor()
{
    mywidget->penColor = QColorDialog::getColor();
    penColorButton->setStyleSheet("background-color: "+mywidget->penColor.name()+";");
}

void MainWindow::setBrushColor()
{
    mywidget->brushColor = QColorDialog::getColor();
    brushColorButton->setStyleSheet("background-color: "+mywidget->brushColor.name()+";");
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

void MainWindow::on_actionNone_triggered()
{
    mywidget->setBrushNone();
}

void MainWindow::on_actionFull_triggered()
{
    mywidget->setBrushFull();
}
