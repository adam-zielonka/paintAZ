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

void NewFileDialog::on_buttonBox_accepted()
{
    accepted = true;
    height = ui->lineEditHeight->text().toInt();
    width = ui->lineEditWidth->text().toInt();
}
