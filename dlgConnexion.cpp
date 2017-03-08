#include "dlgConnexion.h"
#include "ui_dlgConnexion.h"
#include <QSqlDatabase>
#include <QDebug>


DlgConnexion::DlgConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgConnexion)
{
    ui->setupUi(this);
    enableButConnexion();
}

DlgConnexion::~DlgConnexion()
{
    delete ui;
}

//avtive ou désactive le bouton connexion en fonction du remplissage des champs.
void DlgConnexion::enableButConnexion()
{
    if(ui->lineEditUser->text()=="")
    {
        ui->butConnexion->setEnabled(false);
    }
    else
    {
        if(ui->lineEditPassword->text()=="")
        {
            ui->butConnexion->setEnabled(false);
        }
        else
        {
            ui->butConnexion->setEnabled(true);
        }
    }
}

void DlgConnexion::on_lineEditUser_textChanged(const QString &arg1)
{
    ui->butConnexion->setEnabled(true);
}

void DlgConnexion::on_lineEditPassword_textChanged(const QString &arg1)
{
    ui->butConnexion->setEnabled(true);
}

void DlgConnexion::on_butConnexion_clicked()
{
    QString qsUser =  ui->lineEditUser->text();
    QString qsMdp = ui->lineEditPassword->text();

    QSqlDatabase maBase=QSqlDatabase::addDatabase("QMYSQL");
    maBase.setDatabaseName("mysql");
    maBase.setHostName("localhost");
    maBase.setUserName(qsUser);
    maBase.setPassword(qsMdp);
    if(maBase.open())
    {
        QDialog::accept();

    }else
    {
        qDebug()<<"connection a la base a echoué"<<endl;
    }

}


void DlgConnexion::on_butCancel_clicked()
{
    QDialog::reject();
}
