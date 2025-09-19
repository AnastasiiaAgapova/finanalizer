#include "mainwindow.h"

#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QFileDialog>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QHeaderView>
#include <QFileDialog>
#include <QLabel>

#include "appconfig.h"
#include "daterangeedit.h"
#include "piechart.h"
#include "piechartbuilder.h"
#include "transactions/filters/timeperiod.h"
#include "transactions/filters/type.h"
#include "transactions/filters/complex.h"
#include "transactions/threecolumncsvparser.h"
#include "transactions/simplecategorydetector.h"
#include "transactions/databasestorage.h"
#include "databasemodel.h"
#include "widgets/databesasortfilterproxymodel.h"

namespace Widgets
{

PieChart *initializeChart()
{
    PieChart *chart = new PieChart;
    chart->setTheme(QChart::ChartThemeBlueIcy);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    return chart;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , _model(new DatabaseModel(this))
    , _proxyModel(new DatabesaSortFilterProxyModel(this))
    , _database(new Transactions::Database(this))
{
    _model->setDatabase(_database);
    QObject::connect(_database, &Transactions::Database::changed, this, &MainWindow::onDatabaseChaned);
    _proxyModel->setSourceModel(_model);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    QTableView *transactionsView = new QTableView(centralWidget);
    leftLayout->addWidget(transactionsView);

    transactionsView->setModel(_proxyModel);
    transactionsView->horizontalHeader()->setStretchLastSection(true);
    transactionsView->setSortingEnabled(true);

    QPushButton *addDataButton = new QPushButton("Add...", centralWidget);
    leftLayout->addWidget(addDataButton);
    QObject::connect(addDataButton, SIGNAL(pressed()), this, SLOT(addData()));

    _dateRangeEdit = new DateRangeEdit(centralWidget);
    rightLayout->addWidget(_dateRangeEdit, 0, Qt::AlignLeft);
    QObject::connect(_dateRangeEdit, &DateRangeEdit::dateRangeChanged, this, &MainWindow::onDateRangeChanged);

    PieChart *incomeChart = initializeChart();
    PieChart *outcomeChart = initializeChart();

    QChartView *incomeChartView = new QChartView(incomeChart, centralWidget);
    incomeChartView->setRenderHint(QPainter::Antialiasing);

    QChartView *outcomeChartView = new QChartView(outcomeChart, centralWidget);
    outcomeChartView->setRenderHint(QPainter::Antialiasing);

    rightLayout->addWidget(new QLabel("Incomes"), 0, Qt::AlignHCenter);
    rightLayout->addWidget(incomeChartView);
    rightLayout->addWidget(new QLabel("Outcomes"), 0, Qt::AlignHCenter);
    rightLayout->addWidget(outcomeChartView);

    _incomeBuilder = new PieChartBuilder(_database, incomeChart, this);
    _outcomeBuilder = new PieChartBuilder(_database, outcomeChart, this);

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
    QStringList filePathList = QFileDialog::getOpenFileNames(
        this,
        "Open CSV File",
        QString(),
        "CSV Files (*.csv);;All Files (*)"
        );

    if (!filePathList.isEmpty())
    {
        for (auto &filePath : filePathList) {
            Transactions::ThreeColumnCsvParser parser;
            Transactions::SimpleCategoryDetector detector;
            parser.setCategoryDetector(&detector);
            _database->addTransactions(parser.load(filePath));
        }
    }
}

void MainWindow::onDateRangeChanged()
{
    auto timeFilter = std::make_shared<Transactions::Filters::TimePeriod>(_dateRangeEdit->startDate(), _dateRangeEdit->endDate());
    QList<std::shared_ptr<Transactions::Filter>> incomeFilters;
    incomeFilters << std::make_unique<Transactions::Filters::Type>(Transactions::Transaction::INCOME)
                  << timeFilter;
    QList<std::shared_ptr<Transactions::Filter>> outcomeFilters;
    outcomeFilters << std::make_unique<Transactions::Filters::Type>(Transactions::Transaction::OUTCOME)
                  << timeFilter;

    _incomeBuilder->setFilter(std::make_shared<Transactions::Filters::Complex>(incomeFilters));
    _outcomeBuilder->setFilter(std::make_shared<Transactions::Filters::Complex>(outcomeFilters));

    _proxyModel->setFilter(timeFilter);
}

void MainWindow::onDatabaseChaned()
{
    _dateRangeEdit->setMaxDateRange(_database->startDate(), _database->endDate());
}
}
