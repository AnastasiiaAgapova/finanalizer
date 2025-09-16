#ifndef TIMEPERIOD_H
#define TIMEPERIOD_H

#include <QDate>

#include "transactions/filter.h"

namespace Transactions
{
namespace Filters
{
class TimePeriod : public Filter
{
public:
    TimePeriod(const QDate &start, const QDate &end);

    virtual bool isMatch(const Transaction *transaction) const;

private:
    QDate _start;
    QDate _end;
};
}
}

#endif // TIMEPERIOD_H
