#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"

AddTaskDialog::AddTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskDialog)
{
    ui->setupUi(this);
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

void AddTaskDialog::on_acceptBtn_clicked()
{
    QString title = ui->titleEdit->text();
    QString description = ui->descriptionEdit->toPlainText();
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    curDate = dateTime.date();

    if (title.isEmpty()) {
        QMessageBox::information(this, "Пустое поле", "Пожалуйста, введите заголовок задачи.");
    } else {
        QSqlQuery query;
        query.prepare("INSERT INTO tasks (title, description, date) VALUES (:title, :description, :date);");
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":date", dateTime);

        if (!query.exec()) {
            qWarning() << "Ошибка выполнения запроса:";
        } else {
            accept();
            emit taskAdded(curDate);
        }
    }
}
