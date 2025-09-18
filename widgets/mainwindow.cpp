#include "mainwindow.h"

#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QFileDialog>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QHeaderView>
#include <QFileDialog>

#include "appconfig.h"
#include "daterangeedit.h"
#include "piechart.h"
#include "piechartbuilder.h"
#include "transactions/filters/timeperiod.h"
#include "transactions/threecolumncsvparser.h"
#include "transactions/simplecategorydetector.h"
#include "transactions/databasestorage.h"

namespace Widgets
{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , _model(new DatabaseModel(this))
    , _database(new Transactions::Database(this))
{
    _model->setDatabase(_database);
    QObject::connect(_database, &Transactions::Database::changed, this, &MainWindow::onDatabaseChaned);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    QTableView *transactionsView = new QTableView(centralWidget);
    leftLayout->addWidget(transactionsView);

    transactionsView->setModel(_model);
    transactionsView->horizontalHeader()->setStretchLastSection(true);

    QPushButton *addDataButton = new QPushButton("Add...", centralWidget);
    leftLayout->addWidget(addDataButton);
    QObject::connect(addDataButton, SIGNAL(pressed()), this, SLOT(addData()));

    _dateRangeEdit = new DateRangeEdit(centralWidget);
    rightLayout->addWidget(_dateRangeEdit, 0, Qt::AlignLeft);
    QObject::connect(_dateRangeEdit, &DateRangeEdit::dateRangeChanged, this, &MainWindow::onDateRangeChanged);

    PieChart *chart = new PieChart;
    chart->setTheme(QChart::ChartThemeBlueIcy);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart, centralWidget);
    chartView->setRenderHint(QPainter::Antialiasing);
    rightLayout->addWidget(chartView);

    _builder = new PieChartBuilder(_database, chart, this);

    openDatabase();

    resize(1000, 500);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Transactions::DatabaseStorage().save(_database, AppConfig::instance().databasePath());
    event->accept();
}

void MainWindow::openDatabase()
{
    Transactions::DatabaseStorage().load(_database, AppConfig::instance().databasePath());
}

void MainWindow::addData()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open CSV File",
        QString(),
        "CSV Files (*.csv);;All Files (*)"
        );

    if (!filePath.isEmpty())
    {
        Transactions::ThreeColumnCsvParser parser;
        Transactions::SimpleCategoryDetector detector;
        parser.setCategoryDetector(&detector);
        _database->addTransactions(parser.load(filePath));
    }
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
