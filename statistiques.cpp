#include "statistiques.h"
#include "ui_statistiques.h"
#include "employee.h"
#include <QGridLayout>
#include <QWidget>
#include <QtCore>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <qwindow.h>
#include <QVariant>
#include "QDialog"
#include "QWidget"

Statistiques::Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistiques)
{
    QBarSet *set=new QBarSet("Nombre des Employees");
        *set<<E.Calcul("Employee")<<E.Calcul("Admin");
        QBarSeries *series=new QBarSeries();
        series->append(set);
        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des Employee");
        chart->setAnimationOptions(QChart::AllAnimations);
        QStringList mois;
        mois<<"Employee"<<"Admin";
        QBarCategoryAxis *axis=new QBarCategoryAxis();
        axis->append(mois);
        chart->createDefaultAxes();
        chart->setAxisX(axis,series);

        QChartView *chartview=new QChartView(chart);

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(chartview, 0, 0);
        this->setLayout(mainLayout);
    }

Statistiques::~Statistiques()
{
    delete ui;
}
