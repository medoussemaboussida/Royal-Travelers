#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "employee.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_TrieNom_clicked();

    void on_TriePrenom_clicked();

    void on_pb_chercher_clicked();

    void on_pb_export_clicked();

    void on_pb_statistique_clicked();

    void on_pb_chat_clicked();
    void on_groupBox_clicked();

    void on_pushButton_ajouter_2_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_pushButton_afficher_clicked();

    void on_pushButton_chercher_clicked();

    void on_pushButton_pdf_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_calcul_2_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_qr_2_clicked();

    void on_pushButton_stat_clicked();

public slots :
    void openDialog();
private:
    Ui::Dialog *ui;
    Employee E;

};

#endif // DIALOG_H
