#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);
    accepted = false;
}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}

int NewFileDialog::getWidth()
{
    return width;
}

int NewFileDialog::getHeight()
{
    return height;
}

bool NewFileDialog::checkAccept()
{
    if(accepted)
    {
        accepted = false;
        return true;
    }
    else
        return false;
}

void NewFileDialog::on_buttonBox_accepted()
{
    accepted = true;
    height = ui->lineEditHeight->text().toInt();
    width = ui->lineEditWidth->text().toInt();
}
