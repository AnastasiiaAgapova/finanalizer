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
    QObject::connect(_database, &Transactions::Database::changed, this, &PieChartBuilder::rebuild);
}

void PieChartBuilder::setFilter(std::shared_ptr<Transactions::Filter> filter)
{
    _currentFilter = std::move(filter);
    rebuild();
}

void PieChartBuilder::rebuild()
{
    if (nullptr == _database || nullptr == _pieChart)
        return;
    auto transactions = _currentFilter
                                    ? _database->filterTransactions(_currentFilter.get())
                                    : _database->transactions();
    QMap<QString,int> categorySums;
    foreach (auto &transaction, transactions)
    {
        if (categorySums.contains(transaction->category()))
            categorySums[transaction->category()] += abs(transaction->amount());
        else
            categorySums.insert(transaction->category(), abs(transaction->amount()));
    }

    _categorySeries->clear();
    for (auto it = categorySums.begin(); it != categorySums.end(); ++it)
        *_categorySeries << new NamedPieSlice(it.value(), it.key());

    _pieChart->addSeries(_categorySeries);

}
}
