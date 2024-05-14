#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H

#include <QChartView>
#include <QObject>
#include <QLineSeries>

class MyChartView : public QChartView
{
    Q_OBJECT
public:
    MyChartView(QWidget *parent = nullptr): QChartView(parent) {}
    void handleClickedPoint(const QPointF &point);
    void addSeries(QLineSeries *series);
    QLineSeries* series;
};

#endif // MYCHARTVIEW_H
