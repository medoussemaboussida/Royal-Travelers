#ifndef STAT_LOG_H
#define STAT_LOG_H
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include "logement.h"
#include "QDialog"
#include <QWidget>
QT_CHARTS_USE_NAMESPACE


namespace Ui {
class statistiqueee :public stat{};
}

class statistiqueee : public QDialog
{
    Q_OBJECT

public:
    explicit statistiqueee(QWidget *parent = nullptr);
    ~statistiqueee();

private:
    Ui::statistiqueee *ui;
    stat s;
    logement l;
};

#endif // STAT_LOG_H
