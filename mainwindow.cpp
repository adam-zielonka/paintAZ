#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    newFile = new NewFileDialog();
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

void MainWindow::on_actionNew_triggered()
{
    newFile->exec();
    if(newFile->accepted)
    {
        mywidget->image = QImage(newFile->width,newFile->height, QImage::Format_RGB32);
        mywidget->image.fill(Qt::white);
        newFile->accepted = false;
        mywidget->update();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName();
    mywidget->image.load(file);
    mywidget->update();
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName();
    mywidget->image.save(file);
}
