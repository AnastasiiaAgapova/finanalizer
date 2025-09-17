#include "mainwindow.h"

#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QFileDialog>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QHeaderView>

#include "daterangeedit.h"
#include "piechart.h"
#include "piechartbuilder.h"
#include "transactions/filters/timeperiod.h"

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
    transactionsView->horizontalHeader()->setStretchLastSection(true);

    QPushButton *openDatabaseButton = new QPushButton("Open", centralWidget);
    leftLayout->addWidget(openDatabaseButton);
    connect(openDatabaseButton, SIGNAL(pressed()), this, SLOT(openDatabase()));

    _dateRangeEdit = new DateRangeEdit(centralWidget);
    rightLayout->addWidget(_dateRangeEdit, 0, Qt::AlignLeft);
    connect(_dateRangeEdit, &DateRangeEdit::dateRangeChanged, this, &MainWindow::onDateRangeChanged);

    PieChart *chart = new PieChart;
    chart->setTheme(QChart::ChartThemeBlueIcy);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart, centralWidget);
    chartView->setRenderHint(QPainter::Antialiasing);
    rightLayout->addWidget(chartView);

    _builder = new PieChartBuilder(_database, chart, this);

    connect(_database, &Transactions::Database::changed, this, &MainWindow::onDatabaseChaned);

    resize(1000, 500);


}

void MainWindow::openDatabase()
{
    _database->setFileName("..\\..\\examples\\database.json");
    _database->load();
    _model->setDatabase(_database);
}

void MainWindow::onDateRangeChanged()
{
    _builder->setFilter(std::make_unique<Transactions::Filters::TimePeriod>(_dateRangeEdit->startDate(), _dateRangeEdit->endDate()));
}

void MainWindow::onDatabaseChaned()
{
    _dateRangeEdit->setMaxDateRange(_database->startDate(), _database->endDate());
}
}
