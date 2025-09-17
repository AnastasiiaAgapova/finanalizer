#ifndef PIECHARTBUILDER_H
#define PIECHARTBUILDER_H

#include <QObject>

#include "transactions/database.h"
#include "transactions/filter.h"

#include "piechart.h"

class QPieSeries;

namespace Widgets
{
class PieChartBuilder : public QObject
{
    Q_OBJECT
public:
    PieChartBuilder(Transactions::Database *database, PieChart *pieChart, QObject *parent = nullptr);
    void setFilter(std::unique_ptr<Transactions::Filter> filter);

public slots:
    void rebuild();

private:
    Transactions::Database *_database;
    PieChart *_pieChart;
    std::unique_ptr<Transactions::Filter> _currentFilter = nullptr;
    QPieSeries *_categorySeries;
};
}

#endif // PIECHARTBUILDER_H
