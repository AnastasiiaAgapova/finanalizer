#include "complex.h"
namespace Transactions
{
namespace Filters
{
    Complex::Complex(QList<std::shared_ptr<Filter>> filters)
        : _filters(filters)
    {

    }

    bool Complex::isMatch(const std::shared_ptr<Transaction> &transaction) const
    {
        for (auto &filter : _filters) {
            if (!filter->isMatch(transaction))
                return false;
        }
        return true;
    }
}
}
