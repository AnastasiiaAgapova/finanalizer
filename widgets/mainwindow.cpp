#include "mainwindow.h"

#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QFileDialog>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

#include "piechart.h"
#include "piechartbuilder.h"

namespace Widgets
{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , _model(new DatabaseModel(this))
    , _database(new Transactions::Database(this))
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    QTableView *transactionsView = new QTableView(centralWidget);
    leftLayout->addWidget(transactionsView);
    _model->setDatabase(_database);
    transactionsView->setModel(_model);

    QPushButton *openDatabaseButton = new QPushButton("Open", centralWidget);
    leftLayout->addWidget(openDatabaseButton);
    connect(openDatabaseButton, SIGNAL(pressed()), this, SLOT(openDatabase()));

    PieChart *chart = new PieChart;
    chart->setTheme(QChart::ChartThemeBlueIcy);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart, centralWidget);
    chartView->setRenderHint(QPainter::Antialiasing);
    rightLayout->addWidget(chartView);

    PieChartBuilder *builder = new PieChartBuilder(_database, chart, this);


}

void MainWindow::openDatabase()
{
    _database->setFileName("C:\\workspace\\finanalizer\\examples\\database.json");
    _database->load();
    _model->setDatabase(_database);
}
}
