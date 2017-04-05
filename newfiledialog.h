#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFileDialog(QWidget *parent = 0);
    ~NewFileDialog();
    int height;
    int width;
    bool accepted;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewFileDialog *ui;
};

#endif // NEWFILEDIALOG_H
