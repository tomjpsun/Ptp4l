#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H

#include <QChartView>
#include <QObject>
#include <QLineSeries>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class MyChartView : public QChartView
{
    Q_OBJECT
public:
    MyChartView(QWidget *parent = nullptr): QChartView(parent) {}
    void handleClickedPoint(const QPointF &point);
    void plot(QLineSeries *series);
    QLineSeries* series;
};

#endif // MYCHARTVIEW_H
