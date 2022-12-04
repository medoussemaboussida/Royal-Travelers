#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "dialog.h"
#include <dialog.h>
#include "connection.h"
#include "employee.h"
#include "arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//Employee E;
private slots:

    void on_pushButton_2_clicked();
    void update_nb();
void read();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
      QSerialPort *serial;
          QString portname;
    Employee E;
          bool arduino_available;
           void arduino_init();
            QByteArray data; // variable contenant les données reçues
             Arduino A;
};
#endif // MAINWINDOW_H
