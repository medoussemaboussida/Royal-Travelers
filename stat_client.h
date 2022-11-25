#ifndef STAT_CLIENT_H
#define STAT_CLIENT_H


#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include "client.h"

QT_CHARTS_USE_NAMESPACE


//class statistiques;

namespace Ui {
class statistiques : public stat{};
}

class statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit statistiques(QWidget *parent = nullptr);
   /* virtual */~statistiques();

private:
    Ui::statistiques *ui;
    stat s;
    client c ;
};

#endif // STAT_CLIENT_H
