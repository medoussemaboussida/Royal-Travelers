#include "stat_log.h"
#include "ui_statistique.h"
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
#include"logement.h"
statistiqueee::statistiqueee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiqueee)
{
 //  ui->setupUi(this);
    QBarSet *set=new QBarSet("Statistiques par prix");
        *set<<l.calculer(0,500)<<l.calculer(501,1000)<<l.calculer(1001,2000);
        QBarSeries *series=new QBarSeries();
        series->append(set);
        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setTitle("logement");
        chart->setAnimationOptions(QChart::AllAnimations);
        QStringList mois;
        mois<<"[0..500]"<<"[501..1000]"<<"[1001..2000]";
        QBarCategoryAxis *axis=new QBarCategoryAxis();
        axis->append(mois);
        chart->createDefaultAxes();
        chart->setAxisX(axis,series);

        QChartView *chartview=new QChartView(chart);

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(chartview, 0, 0);
        this->setLayout(mainLayout);
}

statistiqueee::~statistiqueee()
{
    delete ui;
}
