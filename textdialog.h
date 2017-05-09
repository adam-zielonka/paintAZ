#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>

namespace Ui {
class TextDialog;
}

class TextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextDialog(QWidget *parent = 0);
    ~TextDialog();
    QFont GetFont();
    QString GetText();
    bool checkAccept();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TextDialog *ui;
    bool accepted;
};

#endif // TEXTDIALOG_H
