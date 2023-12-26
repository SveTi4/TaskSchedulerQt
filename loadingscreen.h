#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QDialog>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>

class LoadingScreen : public QDialog
{
    Q_OBJECT
public:
    explicit LoadingScreen(QWidget *parent = nullptr); // Добавляем объявление конструктора
};

#endif // LOADINGSCREEN_H
