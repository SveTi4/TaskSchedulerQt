#include "loadingscreen.h"

LoadingScreen::LoadingScreen(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(this);
    QMovie *movie = new QMovie(":/loading-wtf.gif");
    label->setMovie(movie);
    layout->addWidget(label);
    movie->start();
    setLayout(layout);
}
