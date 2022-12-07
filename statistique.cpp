#include "statistique.h"
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

statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
    QBarSet *set=new QBarSet("transport");
        *set<<T.calculer1(0,19)<<T.calculer1(20,999999);
        QBarSeries *series=new QBarSeries();
        series->append(set);
        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques par capacitè");
        chart->setAnimationOptions(QChart::AllAnimations);
        QStringList mois;
        mois<<"Moins que 20"<<"Plus que 20 ";
        QBarCategoryAxis *axis=new QBarCategoryAxis();
        axis->append(mois);
        chart->createDefaultAxes();
        chart->setAxisX(axis,series);

        QChartView *chartview=new QChartView(chart);

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(chartview, 0, 0);
        this->setLayout(mainLayout);
}

statistique::~statistique()
{
    delete ui;
}
