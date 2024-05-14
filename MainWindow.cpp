#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QValueAxis>
#include <QLayout>
#include <QFileDialog>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include <QLineSeries>
#include "MyChartView.h"

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

MyChartView* MainWindow::initChartView()
{
    QChart* chart = new QChart();
    QValueAxis* axisX = new QValueAxis();
    QValueAxis* axisY = new QValueAxis();
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    axisX->setRange(0, 30);
    axisY->setRange(0, 5);
    MyChartView* chartView = new MyChartView(this);
    chartView->setChart(chart);

    return chartView;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, QObject::tr("Text file"),
                                                    qApp->applicationDirPath(), QObject::tr("Files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file for reading:" << qPrintable(file.errorString());
        return;
    }

    QTextStream in(&file);
    QList<Ptp4Data> table;

    while (!in.atEnd())
    {
        QString fileLine = in.readLine();
        searchLine(fileLine, table);
    }
    qDebug() << "table size:" << table.size();
    file.close();
    if (table.size() == 0) {
        return;
    }
    originalData = table;
    float xMax = table[table.size() - 1].x;
    float xMin = table[0].x;
    ui->xMax->setText(QString::number(xMax));
    ui->xMin->setText(QString::number(xMin));
    draw(table);
}

void MainWindow::searchLine(QString line, QList<Ptp4Data> &table)
{
    QRegularExpression re(R"(\[(\d+\.\d+)\].*?master offset\s+(-?\d+).*?freq\s+([+-]?\d+).*?path delay\s+(\d+))");

    QRegularExpressionMatch match = re.match(line);

    if (match.hasMatch()) {
        QString x = match.captured(1);
        QString y1 = match.captured(2);
        QString y2 = match.captured(3);
        QString y3 = match.captured(4);

        // qDebug() << "x:" << x
        //          << ", y1:" << y1
        //          << ", y2:" << y2
        //          << ", y3:" << y3;
        Ptp4Data data;
        data.x = x.toDouble();
        data.y1 = y1.toDouble();
        data.y2 = y2.toDouble();
        data.y3 = y3.toDouble();
        table.append(data);
    }
}


void MainWindow::addSeriesToChart(MyChartView* chartView, QList<Ptp4Data> &data, int yIndex)
{
    QLineSeries *series = new QLineSeries();

    for (const Ptp4Data &pt : data) {
        switch (yIndex) {
        case 1:
            series->append(pt.x, pt.y1);
            break;
        case 2:
            series->append(pt.x, pt.y2);
            break;
        case 3:
            series->append(pt.x, pt.y3);
            break;
        }
    }

    chartView->addSeries(series);
}


void MainWindow::draw(QList<Ptp4Data>& table)
{
    addSeriesToChart(chartViewy1, table, 1);
    addSeriesToChart(chartViewy2, table, 2);
    addSeriesToChart(chartViewy3, table, 3);
}

void MainWindow::on_redraw_clicked()
{
    QList<Ptp4Data> table;
    for (const Ptp4Data &pt : originalData) {
        if (pt.x >= ui->xMin->text().toDouble() && pt.x <= ui->xMax->text().toDouble()) {
            table.append(pt);
        }
    }
    draw(table);
}


