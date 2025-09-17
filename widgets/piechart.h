#ifndef PIECHART_H
#define PIECHART_H

#include <QtCharts/QChart>

namespace Widgets
{
class PieChart : public QChart
{
public:
    PieChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
};
}

#endif // PIECHART_H
