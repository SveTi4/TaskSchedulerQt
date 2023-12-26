#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    ui->textBrowser->setSource(
        QUrl::fromLocalFile(":/HelpResources/index.html"));
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
