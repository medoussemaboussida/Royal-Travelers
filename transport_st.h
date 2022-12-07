#ifndef TRANSPORT_ST_H
#define TRANSPORT_ST_H
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include"transport.h"
//class statistiques;
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class statistiquee : public stat{};
}

class statistiquee : public QWidget
{
    Q_OBJECT

public:
    explicit statistiquee(QWidget *parent = nullptr);
   /* virtual */~statistiquee();

private:
    Ui::statistiquee *ui;
    stat s;
    Transport T ;
};

#endif // TRANSPORT_ST_H
