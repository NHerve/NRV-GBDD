#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_buttonBox_accepted()
{
    close();
}
