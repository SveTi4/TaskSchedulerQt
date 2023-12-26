#include "mainwindow.h"
#include "loadingscreen.h"
#include "authregdialog.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>

//#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingScreen loadingScreen;
    loadingScreen.show();
    QApplication::processEvents();

    AuthRegDialog auth;
    auth.setModal(true);
    auth.exec();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    QString dbPath = QCoreApplication::applicationDirPath() + QDir::separator() + "data.db";
    QString dbPath = "/Users/glitch/Documents/qtLabs/cw/MyTaskSchedulerLocal/data.db";
    db.setDatabaseName(dbPath);

//    qDebug() << "Путь к базе данных из ресурсов:" << QResource("qrc:/loading.gif").absoluteFilePath();

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть базу данных: "/* + db.lastError().text()*/);
        return -1;
    }

    loadingScreen.hide();

    MainWindow w;
    w.readSettings();
    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    w.setStyleSheet(file.readAll());
    w.show();

    return a.exec();
}
