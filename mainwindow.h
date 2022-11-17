#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <dialog.h>
#include "connection.h"
#include "employee.h"
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

private:
    Ui::MainWindow *ui;

    Employee E;
};
#endif // MAINWINDOW_H
