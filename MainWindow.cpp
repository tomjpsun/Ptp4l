#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QValueAxis>
#include <QLayout>
#include <QFileDialog>
#include <QFile>
#include <QRegularExpression>

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
    while (!in.atEnd())
    {
        QString fileLine = in.readLine();
        searchLine(fileLine);
    }
    file.close();
}

void MainWindow::searchLine(QString line)
{
    QRegularExpression re(R"(\[(\d+\.\d+)\].*?master offset\s+(-?\d+).*?freq\s+([+-]?\d+).*?path delay\s+(\d+))");

    QRegularExpressionMatch match = re.match(line);

    if (match.hasMatch()) {
        QString x = match.captured(1);
        QString y1 = match.captured(2);
        QString y2 = match.captured(3);
        QString y3 = match.captured(4);

        qDebug() << "x:" << x
                 << ", y1:" << y1
                 << ", y2:" << y2
                 << ", y3:" << y3;
    }
}
