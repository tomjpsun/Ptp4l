#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H

#include <QChartView>
#include <QObject>

class MyChartView : public QChartView
{
    Q_OBJECT
public:
    MyChartView(QWidget *parent = nullptr): QChartView(parent) {}
    void handleClickedPoint(const QPointF &point);
};

#endif // MYCHARTVIEW_H
