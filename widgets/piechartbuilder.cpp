#include "piechartbuilder.h"

#include <QtCharts/QPieSeries>

#include "namedpieslice.h"

namespace Widgets
{
PieChartBuilder::PieChartBuilder(Transactions::Database *database, PieChart *pieChart, QObject *parent)
    : QObject(parent)
    , _database(database)
    , _pieChart(pieChart)
    , _categorySeries(new QPieSeries(this))
{
    connect(_database, &Transactions::Database::changed, this, &PieChartBuilder::rebuild);
}

void PieChartBuilder::setFilter(Transactions::Filter *filter)
{
    _currentFilter = filter;
    rebuild();
}

void PieChartBuilder::rebuild()
{
    if (nullptr == _database || nullptr == _pieChart)
        return;
    QList<const Transactions::Transaction *> transactions = _currentFilter ?
                                                                _database->filterTransactions(_currentFilter)
                                                                           : _database->transactions();
    QMap<QString,int> categorySums;
    foreach (auto transaction, transactions)
    {
        if (categorySums.contains(transaction->category()))
            categorySums[transaction->category()] += transaction->amount();
        else
            categorySums.insert(transaction->category(), transaction->amount());
    }

    _categorySeries->clear();
    for (auto it = categorySums.begin(); it != categorySums.end(); ++it)
        *_categorySeries << new NamedPieSlice(it.value(), it.key());

    _pieChart->addSeries(_categorySeries);

}
}
