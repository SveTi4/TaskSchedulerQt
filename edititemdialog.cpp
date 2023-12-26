#include "edititemdialog.h"
#include "ui_edititemdialog.h"

#include <QFileDialog>

EditItemDialog::EditItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditItemDialog)
{
    ui->setupUi(this);
}

void EditItemDialog::setData(const QString& id, const QString& title, const QString& description, const QDateTime& date) {
    ui->lineEdit->setText(title);
    ui->textEdit->setText(description);
    ui->dateTimeEdit->setDateTime(date);
    editId = id;
    qDebug() << date;
}

EditItemDialog::~EditItemDialog()
{
    delete ui;
}

void EditItemDialog::on_editBtn_clicked()
{
    QString title = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    if (title.isEmpty()) {
        QMessageBox::information(this, "Пустое поле", "Пожалуйста, введите заголовок задачи.");
    } else {
        QSqlQuery query;
        query.prepare("UPDATE tasks SET title = :title, description = :description, date = :date WHERE id = :id");
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":date", dateTime);
        query.bindValue(":id", editId);

        if (!query.exec()) {
            qWarning() << "Ошибка выполнения запроса:";
        } else {
            accept();
        }
    }
}


void EditItemDialog::on_delBtn_clicked()
{
    QDateTime dateTime = ui->dateTimeEdit->dateTime();
    curDate = dateTime.date();

    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", editId);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:";
    } else {
        accept();
        emit taskDeleted(curDate);
    }
}


void EditItemDialog::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), QDir::homePath(), tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
//            // Ваша текстовая информация, которую вы хотите сохранить
            QString lineEditText = ui->lineEdit->text();
            QString text1 = ui->textEdit->toPlainText();
            QDateTime dateTime = ui->dateTimeEdit->dateTime();

            out << lineEditText + "\n" + text1 + "\n" + dateTime.toString();
            file.close();
        } else {
            // Обработка ошибки открытия файла
        }
    }
}

