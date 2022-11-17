#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include "employee.h"
#include "QDialog"

QT_CHARTS_USE_NAMESPACE


//class statistiques;

namespace Ui {
class Statistiques : public stat{};
}

class Statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit Statistiques(QWidget *parent = nullptr);
   /* virtual */~Statistiques();

private:
    Ui::Statistiques *ui;
    stat S;
    Employee E ;
};

#endif // STATISTIQUES_H
