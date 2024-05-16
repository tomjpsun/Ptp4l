#include "MyChartView.h"
#include <QXYSeries>


void MyChartView::handleClickedPoint(const QPointF &p)
{
    qDebug() << "clicked point:" << p;
    QList<QPointF> points = series->points();
    // find nearest x to p.x
    int index = 0;
    for (index = 0; index < points.size() - 1; index++) {
        if ( sgn(points[index].x() - p.x()) !=
             sgn(points[index+1].x() - p.x()) ) {
            break;
        }
    }
    // choose the nearest from points[i] and points[i+1]
    double d1 = qAbs(points[index].x() - p.x());
    double d2 = qAbs(points[index+1].x() - p.x());
    if (d1 > d2) {
        index++;
    }
    qDebug() << "index:" << index;

    // highlight the point
    series->setPointConfiguration(index,
                                  QXYSeries::PointConfiguration::LabelVisibility,
                                  true);
    series->setPointConfiguration(index,
                                  QXYSeries::PointConfiguration::Visibility,
                                  true);
    series->setPointConfiguration(index,
                                  QXYSeries::PointConfiguration::Size,
                                  3);
}

void MyChartView::plot(QLineSeries* series_)
{
    series = series_;
    QChart *chart = this->chart();
    chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
    // connect series to clicked signal
    connect(series, &QLineSeries::clicked, this, &MyChartView::handleClickedPoint);
}
