#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mywidget = new Widget(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(mywidget);
    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

    penColorButton = new QPushButton(this);
    penColorButton->setStyleSheet("background-color: "+mywidget->getPenColor().name()+";");
    ui->toolBar->addWidget(penColorButton);
    connect(penColorButton,SIGNAL(clicked()),this,SLOT(setPenColor()));

    brushColorButton = new QPushButton(this);
    brushColorButton->setStyleSheet("background-color: "+mywidget->getBrushColor().name()+";");
    ui->toolBar->addWidget(brushColorButton);
    connect(brushColorButton,SIGNAL(clicked()),this,SLOT(setBrushColor()));

    newFile = new NewFileDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPenColor()
{
    mywidget->setPenColor(QColorDialog::getColor());
    penColorButton->setStyleSheet("background-color: "+mywidget->getPenColor().name()+";");
}

void MainWindow::setBrushColor()
{
    mywidget->setBrushColor(QColorDialog::getColor());
    brushColorButton->setStyleSheet("background-color: "+mywidget->getBrushColor().name()+";");
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

void MainWindow::on_actionNew_triggered()
{
    newFile->exec();
    if(newFile->checkAccept())
    {
        mywidget->setNewImage(newFile->getWidth(),newFile->getHeight());
        mywidget->update();
        ui->actionSave->setEnabled(false);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName();
    if(file != "")
    {
        mywidget->loadImage(file);
        mywidget->update();
        ui->actionSave->setEnabled(true);
    }
}

void MainWindow::on_actionSave_triggered()
{
    mywidget->saveImage();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName();
    if(file != "")
    {
        mywidget->saveImage(file);
        ui->actionSave->setEnabled(true);
    }
}
