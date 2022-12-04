#include "stat_mission.h"
#include "ui_statistiques.h"
#include "mission.h"
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

statistiquee::statistiquee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiquee)
{
    QBarSet *set=new QBarSet("Nombre des missions");
        *set<<m.calculer_m("evenement")<<m.calculer_m("seminaire")<<m.calculer_m("reunion");
        QBarSeries *series=new QBarSeries();
        series->append(set);
        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des missions");
        chart->setAnimationOptions(QChart::AllAnimations);
        QStringList mois;
        mois<<"Evenements"<<"seminaires"<<"reunions";
        QBarCategoryAxis *axis=new QBarCategoryAxis();
        axis->append(mois);
        chart->createDefaultAxes();
        chart->setAxisX(axis,series);

        QChartView *chartview=new QChartView(chart);

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(chartview, 0, 0);
        this->setLayout(mainLayout);
    }

statistiquee::~statistiquee()
{
    delete ui;
}
