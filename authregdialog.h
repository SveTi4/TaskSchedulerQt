#ifndef AUTHREGDIALOG_H
#define AUTHREGDIALOG_H

#include <QDialog>

namespace Ui {
class AuthRegDialog;
}

class AuthRegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthRegDialog(QWidget *parent = nullptr);
    ~AuthRegDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AuthRegDialog *ui;
};

#endif // AUTHREGDIALOG_H
