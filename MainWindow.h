#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QChartView>
#include <QChart>
#include <QMainWindow>
#include "MyChartView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


struct Ptp4Data
{
    double x;
    double y1;
    double y2;
    double y3;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MyChartView* initChartView();
    void searchLine(QString line, QList<Ptp4Data> &table);
    void addSeriesToChart(MyChartView* chartView, QList<Ptp4Data> &data, int yIndex);
    void draw(QList<Ptp4Data>& table);
private slots:
    void on_openFile_clicked();
    void on_redraw_clicked();

private:
    Ui::MainWindow *ui;
    MyChartView* chartViewy1;
    MyChartView* chartViewy2;
    MyChartView* chartViewy3;
    QList<Ptp4Data> originalData;
};
#endif // MAINWINDOW_H
