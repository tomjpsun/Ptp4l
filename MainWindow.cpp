#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QValueAxis>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame->setLayout(new QVBoxLayout());
    // 將 chartView 加入 frame 物件
    chartViewy1 = initChartView();
    ui->frame->layout()->addWidget(chartViewy1);
    chartViewy2 = initChartView();
    ui->frame->layout()->addWidget(chartViewy2);
    chartViewy3 = initChartView();
    ui->frame->layout()->addWidget(chartViewy3);
}

QChartView* MainWindow::initChartView()
{
    QChart* chart = new QChart();
    QValueAxis* axisX = new QValueAxis();
    QValueAxis* axisY = new QValueAxis();
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    axisX->setRange(0, 30);
    axisY->setRange(0, 5);
    QChartView* chartView = new QChartView(this);
    chartView->setChart(chart);

    return chartView;
}

MainWindow::~MainWindow()
{
    delete ui;
}
