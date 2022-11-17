#include "chatboxdialog.h"
#include "ui_chatboxdialog.h"
#include "QInputDialog"
#include "QApplication"

ChatBoxDialog::ChatBoxDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatBoxDialog)
{
    ui->setupUi(this);
}

ChatBoxDialog::~ChatBoxDialog()
{
    delete ui;
}

void ChatBoxDialog::on_pb_Done_clicked()
{
    nHostname = ui->hostname->text();
           nPort = ui->port->value();
           accept();
}

void ChatBoxDialog::on_pb_Cancel_clicked()
{
     reject();
}
