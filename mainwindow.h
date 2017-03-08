#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void fillCbBdd();
private slots:
    void on_cbBdd_currentIndexChanged(const QString &arg1);

    void on_listWidgetTable_currentRowChanged(int currentRow);

    void on_textEditRequete_textChanged();

    void on_butExec_clicked();

    void on_butHistoriser_clicked();

    void on_listWidgetHisto_itemClicked(QListWidgetItem *item);

    void on_butDelHisto_clicked();

    void on_butSauvegarder_clicked();

    void on_butSuppr_clicked();

    void on_butOpenHisto_clicked();

    void on_butExport_clicked();

    void on_actionAbout_triggered();

    void on_actionDisconnect_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
