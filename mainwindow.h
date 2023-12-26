#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QModelIndexList>
#include <QSqlDatabase>
#include <helpdialog.h>
#include <QMainWindow>
#include <QCloseEvent>
#include <QListWidget>
#include <QSqlQuery>
#include <QSettings>
#include <QResource>
#include <QPainter>
#include <QAction>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QMenu>
#include <QFile>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void updateListWidget(const QString &currentQuery);
    void readSettings();
    ~MainWindow();

private slots:
    void on_addTask_clicked();

    void on_searchTask_textEdited(const QString &arg1);

    void on_calendarWidget_clicked(const QDate &date);

    void on_allTasks_clicked();

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void updateElapsedTime();

    void slotAbout();

private:
    // В момент закрытия приложения сохраняем положение и размеры окна
    void markDate(QDate &date);
    void unMarkDate(QDate &date);
    void checkDateStatus(QDate &date);
    void closeEvent(QCloseEvent *event);
    QTimer timer;
    QString lastQuery;
    int elapsedSeconds;
    int elapsedMinuts;

//    QSqlDatabase *db;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
