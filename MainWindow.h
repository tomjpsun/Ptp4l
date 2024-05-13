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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QChartView* initChartView();
private:
    Ui::MainWindow *ui;
    QChartView* chartViewy1;
    QChartView* chartViewy2;
    QChartView* chartViewy3;
};
#endif // MAINWINDOW_H
