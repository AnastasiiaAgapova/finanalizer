#ifndef FILTER_H
#define FILTER_H

#include "transaction.h"

namespace Transactions
{
    class Filter
    {
    public:
        virtual ~Filter() {}
        virtual bool isMatch(const std::shared_ptr<Transaction> &transaction) const = 0;
    };
}

#endif // FILTER_H
