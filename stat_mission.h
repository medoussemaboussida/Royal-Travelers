#ifndef STAT_MISSION_H
#define STAT_MISSION_H
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include"mission.h"
//class statistiques;
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class statistiquee : public stat{};
}

class statistiquee : public QDialog
{
    Q_OBJECT

public:
    explicit statistiquee(QWidget *parent = nullptr);
   /* virtual */~statistiquee();

private:
    Ui::statistiquee *ui;
    stat s;
    mission m ;
};

#endif // STAT_MISSION_H
