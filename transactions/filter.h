#ifndef FILTER_H
#define FILTER_H

#include "transaction.h"

namespace Transactions
{
    class Filter
    {
    public:
        virtual ~Filter() {}
        virtual bool isMatch(const Transaction &transaction) const = 0;
    };
}

#endif // FILTER_H
