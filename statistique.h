#ifndef STATISTIQUE_H
#define STATISTIQUE_H
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include "transport.h"
#include "QDialog"
#include <QWidget>
QT_CHARTS_USE_NAMESPACE


namespace Ui {
class statistique;
}

class statistique : public QDialog
{
    Q_OBJECT

public:
    explicit statistique(QWidget *parent = nullptr);
    ~statistique();

private:
    Ui::statistique *ui;
    stat S;
    Transport T ;
};

#endif // STATISTIQUE_H
