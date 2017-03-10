#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlError>
#include <QFileDialog>
#include <QFile>
#include "dialogabout.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillCbBdd();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//rempli la combobox des bdd avec les bdd de l'utilisateur.
void MainWindow::fillCbBdd()
{
    qDebug()<<"fillCbBdd()"<<endl;

    QSqlQuery reqBdd("show databases;");
    while(reqBdd.next())
    {
        QString qsBdd = reqBdd.value(0).toString();
        ui->cbBdd->addItem(qsBdd);

    }
}

void MainWindow::on_cbBdd_currentIndexChanged(const QString &arg1)
{
    qDebug()<<"on_cbBdd_currentIndexChanged"<<endl;
    ui->listWidgetChamp->clear();
    QString qsBddUse = ui->cbBdd->currentText();
    QSqlDatabase dataBase = QSqlDatabase::database();
    dataBase.setDatabaseName(qsBddUse);
    //QSqlQuery reqBddUse("use "+qsBddUse + ";");
    dataBase.close();
    if(dataBase.open())
    {
        ui->listWidgetTable->clear();
        QSqlQuery reqBddTable("show tables;");
        while(reqBddTable.next())
        {
            QString qsNomTable = reqBddTable.value(0).toString();
            ui->listWidgetTable->addItem(qsNomTable);
        }
    }
}


void MainWindow::on_listWidgetTable_currentRowChanged(int currentRow)
{
    qDebug()<<"on_listWidgetTable_currentRowChanged"<<endl;

    if(ui->listWidgetTable->currentItem())
    {
        QString qsTableUse = ui->listWidgetTable->currentItem()->text();
        QSqlQuery reqTableFields("show fields from "+qsTableUse + ";");
        ui->listWidgetChamp->clear();
        while(reqTableFields.next())
        {
            QString qsChamp = reqTableFields.value(0).toString();
            ui->listWidgetChamp->addItem(qsChamp);
        }
    }
}

void MainWindow::on_textEditRequete_textChanged()
{
    QString qsRequete = ui->textEditRequete->toPlainText();
    QSqlQuery requete(qsRequete);
    QSqlRecord rec = requete.record();


    int iTailleReq = requete.size();
    int iLargeReq = rec.count();
    int iCpt=0;

    ui->tableResRequete->setRowCount(0);
    ui->tableResRequete->setRowCount(iTailleReq);
    ui->tableResRequete->setColumnCount(iLargeReq);

    if(requete.exec())
    {
        while(requete.next())
        {
            int iCptLarge=0;
            while(iCptLarge<iLargeReq)
            {

                QString qsReqRes = requete.value(iCptLarge).toString();
                QTableWidgetItem *itemResReq=new QTableWidgetItem(qsReqRes);

                ui->tableResRequete->setItem(iCpt,iCptLarge,itemResReq);
                iCptLarge++;

            }
            iCpt++;
        }
        ui->butExec->setEnabled(false);
        ui->butExec->setStyleSheet("background-color: green;");
        ui->butHistoriser->setEnabled(true);
    }
    else
    {
        ui->butExec->setEnabled(true);
        ui->butExec->setStyleSheet("background-color: red;");
        ui->butHistoriser->setEnabled(false);
    }
}

void MainWindow::on_butExec_clicked()
{
    QString qsRequete = ui->textEditRequete->toPlainText();
    QSqlQuery requete(qsRequete);
    QString qsReqError = requete.lastError().text();

    QMessageBox::critical(this, tr("Error"), qsReqError);
}

void MainWindow::on_butHistoriser_clicked()
{
    ui->listWidgetHisto->addItem(ui->textEditRequete->toPlainText());
}

void MainWindow::on_listWidgetHisto_itemClicked(QListWidgetItem *item)
{
    ui->textEditRequete->setText(item->text());
}

void MainWindow::on_butDelHisto_clicked()
{
    ui->listWidgetHisto->clear();
}

void MainWindow::on_butSauvegarder_clicked()
{
    QString fichier = QFileDialog::getSaveFileName(this,tr("Save File"), "/home", "*.sql");
    QFile file(fichier);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for(int result = 0 ; result < ui->listWidgetHisto->count();result++)
    {
        QString data = ui->listWidgetHisto->item(result)->text();
        out << data << "\n";
    }
}

void MainWindow::on_butSuppr_clicked()
{
    delete ui->listWidgetHisto->currentItem();
}

void MainWindow::on_butOpenHisto_clicked()
{
    QString fichier = QFileDialog::getOpenFileName(this,tr("Open file"), "/home", "*.sql");
    QFile file(fichier);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->listWidgetHisto->clear();
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        ui->listWidgetHisto->addItem(line);
    }
}

void MainWindow::on_butExport_clicked()
{
    QString fichier = QFileDialog::getSaveFileName(this,tr("Save File"), "/home", "*.csv");
    QFile file(fichier);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for(int row = 0 ; row < ui->tableResRequete->rowCount();row++)
    {
        for(int colonne = 0 ; colonne < ui->tableResRequete->columnCount(); colonne++)
        {
            QString data = ui->tableResRequete->item(row,colonne)->text();
            out << data << "\n";
        }

    }

}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout dialAbout;
    dialAbout.exec();
}

