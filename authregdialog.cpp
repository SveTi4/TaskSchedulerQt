#include "authregdialog.h"
#include "ui_authregdialog.h"

AuthRegDialog::AuthRegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthRegDialog)
{
    ui->setupUi(this);
    ui->regBtn->hide();
    ui->regHeading->hide();
    ui->regLabel1->hide();
    ui->regLabel2->hide();
    ui->regLogin->hide();
    ui->regPass1->hide();
}

AuthRegDialog::~AuthRegDialog()
{
    delete ui;
}

void AuthRegDialog::on_pushButton_clicked()
{
//    ui->lineEdit->hide();
}

