#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QChartView>
#include <QChart>
#include <QMainWindow>

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
    QChartView* initChartView();
    void searchLine(QString line, QList<Ptp4Data> &table);
    void addSeriesToChart(QChartView* chartView, QList<Ptp4Data> &data, int yIndex);
    void draw(QList<Ptp4Data>& table);
private slots:
    void on_openFile_clicked();

private:
    Ui::MainWindow *ui;
    QChartView* chartViewy1;
    QChartView* chartViewy2;
    QChartView* chartViewy3;
    QList<Ptp4Data> originalData;
};
#endif // MAINWINDOW_H
