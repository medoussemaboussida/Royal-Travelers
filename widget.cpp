#include "widget.h"
#include "ui_widget.h"
#include "chatboxdialog.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QWidget>
#include "QInputDialog"
#include "QApplication"


DuarteCorporation::widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    nSocket=new QTcpSocket(this);
            connect(nSocket,&QTcpSocket::readyRead,[&](){
                QTextStream T(nSocket);
                auto text=T.readAll();
                ui->textEdit->append(text);
            });
}

DuarteCorporation::widget::~widget()
{
    delete ui;
}

void DuarteCorporation::widget::on_pb_Send_clicked()
{
    QTextStream T(nSocket);
    T << ui->lineEdit_widget->text() << ": " << ui->lineEdit->text();
    nSocket->flush();
    ui->lineEdit->clear();
}


void DuarteCorporation::widget::on_pb_Connect_clicked()
{
    ChatBoxDialog D(this);
        if(D.exec()==QDialog::Rejected)
        {return;
        }
      nSocket->connectToHost(D.hostname() , D.port());

}
