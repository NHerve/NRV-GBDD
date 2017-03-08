#ifndef DLGCONNEXION_H
#define DLGCONNEXION_H

#include <QDialog>


namespace Ui {
class DlgConnexion;
}

class DlgConnexion : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgConnexion(QWidget *parent = 0);
    ~DlgConnexion();
    void enableButConnexion();

private slots:
    void on_lineEditUser_textChanged(const QString &arg1);

    void on_lineEditPassword_textChanged(const QString &arg1);

    void on_butConnexion_clicked();

    void on_butCancel_clicked();

private:
    Ui::DlgConnexion *ui;
};

#endif // DLGCONNEXION_H
