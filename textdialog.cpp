#include "textdialog.h"
#include "ui_textdialog.h"

TextDialog::TextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextDialog)
{
    ui->setupUi(this);
    accepted = false;
}

TextDialog::~TextDialog()
{
    delete ui;
}

QFont TextDialog::GetFont()
{
    QFont font = QFont(ui->fontComboBox->currentFont());
    font.setBold(ui->checkBoxBlod->isChecked());
    font.setItalic(ui->checkBoxItalics->isChecked());
    font.setPointSize(ui->spinBox->value());
    return font;
}

QString TextDialog::GetText()
{
    return ui->lineEdit->text();
}


bool TextDialog::checkAccept()
{
    if(accepted)
    {
        accepted = false;
        return true;
    }
    else
        return false;
}

void TextDialog::on_buttonBox_accepted()
{
    accepted = true;
}
