#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtaskdialog.h"
#include "edititemdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //создание таймера нахождения в программе
    elapsedSeconds = 0;
    elapsedMinuts = 0;
    connect(&timer, &QTimer::timeout, this, &MainWindow::updateElapsedTime);
    timer.start(1000);
    //вывод всех задач
    updateListWidget("SELECT id, title, date, complete, description FROM tasks ORDER BY date ASC");
    //пункт мень справка
    connect(ui->action_2, SIGNAL(triggered()), this, SLOT(slotAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
// справка
void MainWindow::slotAbout() {
    HelpDialog help;
    help.setModal(true);
    help.exec();
}
// обновление таймера
void MainWindow::updateElapsedTime()
{
    elapsedSeconds++;
    if (elapsedSeconds == 60) {
        elapsedSeconds = 0;
        elapsedMinuts++;
    }
    ui->label->setText("Минут: " + QString::number(elapsedMinuts) + " Секунд: " + QString::number(elapsedSeconds));
}
// выделение даты в календаре
void MainWindow::markDate(QDate &date) {
    QTextCharFormat format;
    format.setFontWeight(QFont::ExtraBold);
    format.setFontUnderline(true);

    ui->calendarWidget->setDateTextFormat(date, format);
}
// снятие выделения с даты в календаре
void MainWindow::unMarkDate(QDate &date) {
    QTextCharFormat format;
    format.setFontWeight(QFont::Normal);
    format.setFontUnderline(false);

    ui->calendarWidget->setDateTextFormat(date, format);
}
// обновление списка отображенных задач
void MainWindow::updateListWidget(const QString &currentQuery) {
    if (!QSqlDatabase::database().isValid()) {
        qWarning() << "Недопустимое соединение с базой данных";
        return;
    }

    QSqlQuery query(currentQuery);

    if (query.exec()) {
        ui->listWidget->clear();

        while (query.next()) {
            QListWidgetItem* item = new QListWidgetItem();
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

            bool complete = query.value(3).toBool();
            QString title = query.value(1).toString();
            QDate date = query.value(2).toDate();
            QString formattedDate = query.value(2).toDateTime().toString("dd.MM.yyyy hh:mm");
            QVariant variantDate = formattedDate;
            item->setData(Qt::UserRole + 3, variantDate);

            QString description = query.value(4).toString();

            markDate(date);

            item->setCheckState(complete ? Qt::Checked : Qt::Unchecked);
            item->setText(formattedDate + " – " + title + " (" + description + ")");

            int id = query.value(0).toInt();
            QVariant variantId = id;
            item->setData(Qt::UserRole, variantId);

            QVariant variantTitle = title;
            item->setData(Qt::UserRole + 1, variantTitle);

            QVariant variantDesc = description;
            item->setData(Qt::UserRole + 2, variantDesc);

            ui->listWidget->addItem(item);
        }
    } else {
        qWarning() << "Ошибка выполнения запроса:";
    }
}
// добпаление задачи
void MainWindow::on_addTask_clicked()
{
    AddTaskDialog addD;
    connect(&addD, &AddTaskDialog::taskAdded, this, &MainWindow::markDate);
    addD.setModal(true);
    addD.exec();
    updateListWidget(lastQuery);
}
// Поиск по названию задачи
void MainWindow::on_searchTask_textEdited(const QString &arg1)
{
    QString queryString = "SELECT id, title, date, complete, description FROM tasks WHERE title LIKE '%" + arg1 + "%' ORDER BY date ASC";
    updateListWidget(queryString);
}
// Выбор задач по дате календаря
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QString queryString = "SELECT id, title, date, complete, description FROM tasks WHERE date LIKE '%" + date.toString("yyyy-MM-dd") + "%' ORDER BY date ASC";
    lastQuery = queryString;
    updateListWidget(queryString);
}
// Вывод всех задач
void MainWindow::on_allTasks_clicked()
{
    lastQuery = "SELECT id, title, date, complete, description FROM tasks ORDER BY date ASC";
    updateListWidget("SELECT id, title, date, complete, description FROM tasks ORDER BY date ASC");

    ui->listWidget->setFocus();
}
// Отметка выполеной задачи
void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    Qt::CheckState checkBoxState = item->checkState();

    QVariant id = item->data(Qt::UserRole);
    QSqlQuery query;
    query.prepare("UPDATE tasks SET complete = :complete WHERE id = :id;");
    query.bindValue(":complete", checkBoxState == Qt::Checked ? 1 : 0);
    query.bindValue(":id", id.toInt());

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:";
    }
}
// Открытие окна редактирования задачи
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QVariant id = item->data(Qt::UserRole);
    QVariant title = item->data(Qt::UserRole + 1);
    QVariant description = item->data(Qt::UserRole + 2);
    QVariant date = item->data(Qt::UserRole + 3);

    QString idString = id.toString();
    QString titleString = title.toString();
    QString descriptionString = description.toString();
    QDateTime dateTime = QDateTime::fromString(date.toString(), "dd.MM.yyyy hh:mm");;

    EditItemDialog editD;
    editD.setData(idString, titleString, descriptionString, dateTime);
    connect(&editD, &EditItemDialog::taskDeleted, this, &MainWindow::unMarkDate);
    editD.setModal(true);
    editD.exec();
    updateListWidget(lastQuery);
}
// Чтение их QSettings
void MainWindow::readSettings()
{
    QSettings settings("Company", "MyApp");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}
// Сохранение в QSettings
void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("Company", "MyApp");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}
