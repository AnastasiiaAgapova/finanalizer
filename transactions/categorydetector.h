#ifndef CATEGORYDETECTOR_H
#define CATEGORYDETECTOR_H

#include "transaction.h"

namespace Transactions
{
class CategoryDetector
{
public:
    virtual ~CategoryDetector() {}

    virtual bool detect(std::shared_ptr<Transaction> &transaction) const = 0;
};
}

#endif // CATEGORYDETECTOR_H
