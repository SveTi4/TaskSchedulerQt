#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QListWidgetItem>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QDate>

namespace Ui {
class EditItemDialog;
}

class EditItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditItemDialog(QWidget *parent = nullptr);

    void setData(const QString& id, const QString& title, const QString& description, const QDateTime& date);

    ~EditItemDialog();

private slots:
    void on_editBtn_clicked();

    void on_delBtn_clicked();

    void on_pushButton_clicked();

private:
    QDate curDate;
    QString editId;
    Ui::EditItemDialog *ui;
signals:
    void taskDeleted(QDate &date);
};

#endif // EDITITEMDIALOG_H
