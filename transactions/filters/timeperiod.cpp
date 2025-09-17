#include "timeperiod.h"

namespace Transactions
{
namespace Filters
{
TimePeriod::TimePeriod(const QDate &start, const QDate &end)
    : _start(start)
    , _end(end)
{

}

bool TimePeriod::isMatch(const Transaction &transaction) const
{
    QDate transactionDate = transaction.dateTime().date();
    return transactionDate >= _start && transactionDate <= _end;
}
}
}
