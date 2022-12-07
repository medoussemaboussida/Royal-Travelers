#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "employee.h"
#include "arduino_gadour.h"
#include <qsqlquery.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
int getselectedtran();
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

    void on_pb_ajouter_2_clicked();

    void on_pb_update_clicked();

    void on_pb_supprimer_2_clicked();

    void on_pushButton_aff_clicked();

    void on_pushButton_rech_clicked();

    void on_le_stat_clicked();

    void on_pushButton_2_clicked();

    void on_tab_mission_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void showTime();
    void on_pb_ajouter_3_clicked();

    void on_pb_supprimer_3_clicked();

    void on_UpdateTran_clicked();

    void on_rec_textChanged(const QString &arg1);

    void on_pushButton_01_clicked();

    void on_pushButton_02_clicked();

    void on_pushButton_03_clicked();

    void on_pushButton_04_clicked();

    void on_pushButton_05_clicked();

    void on_pushButton_06_clicked();

    void on_pb_print_clicked();

    void on_Archiver_clicked();

    void on_List_clicked();

    void on_List_2_clicked();

    void on_Archiver_2_clicked();

    void on_Statistique_clicked();

    void on_pushButton_4_clicked();

    void on_pb_supprimer_4_clicked();

    void on_pb_update_2_clicked();

    void on_pushButton_afficherlog_clicked();

    void on_pushButton_cherch_clicked();

    void on_le_PDF_clicked();

    void on_le_stat_2_clicked();

    void on_Check_clicked();

public slots :
    void openDialog();
private:
    Ui::Dialog *ui;
    Employee E;
seriallink *arduino;
};

#endif // DIALOG_H
