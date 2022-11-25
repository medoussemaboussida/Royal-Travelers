#include "stat_client.h"
#include "ui_statistiques.h"
#include <qvariant.h>
#include "client.h"
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

statistiques::statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiques)
{
   // ui->setupUi(this);
       QBarSet *set=new QBarSet("Nombre des budgets");
       *set<<c.calculer1(500,990)<<c.calculer1(1000,2900)<<c.calculer1(3000,4900)<<c.calculer1(5000,6900)<<c.calculer1(7000,10000);
       QBarSeries *series=new QBarSeries();
       series->append(set);
       QChart *chart=new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques des budgets");
       chart->setAnimationOptions(QChart::AllAnimations);
       QStringList mois;
       mois<<"[500dt..990dt]"<<"[1000dt..2900dt]"<<"[3000dt..4900dt]"<<"[5000dt..6900dt]"<<"[7000dt..10000dt]";
       QBarCategoryAxis *axis=new QBarCategoryAxis();
       axis->append(mois);
       chart->createDefaultAxes();
       chart->setAxisX(axis,series);

       QChartView *chartview=new QChartView(chart);

       QGridLayout *mainLayout = new QGridLayout;
       mainLayout->addWidget(chartview, 0, 0);
       this->setLayout(mainLayout);
}
statistiques ::~statistiques()
{
delete ui;
}
