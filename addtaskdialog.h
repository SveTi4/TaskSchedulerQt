#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QWidget>
#include <QSqlQuery>
#include <QString>
#include <QDate>

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = nullptr);

    ~AddTaskDialog();

private slots:


    void on_acceptBtn_clicked();

private:
    QDate curDate;
    Ui::AddTaskDialog *ui;
signals:
    void taskAdded(QDate &date);
};

#endif // ADDTASKDIALOG_H
