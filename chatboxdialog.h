#ifndef CHATBOXDIALOG_H
#define CHATBOXDIALOG_H

#include <QDialog>



namespace Ui {
class ChatBoxDialog;
}

class ChatBoxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatBoxDialog(QWidget *parent = nullptr);
    ~ChatBoxDialog();
        QString hostname() const;
        quint16 port() const;



private slots:
    void on_pb_Done_clicked();

    void on_pb_Cancel_clicked();

private:
    Ui::ChatBoxDialog *ui;
    QString nHostname;
    quint16 nPort;
public :
    inline QString hostname()
    {
        return nHostname;
    }
    inline quint16 port()
    {
        return nPort;
    }


};

#endif // CHATBOXDIALOG_H
