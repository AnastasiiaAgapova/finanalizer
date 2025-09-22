#ifndef SIMPLECATEGORYDETECTOR_H
#define SIMPLECATEGORYDETECTOR_H

#include "categorydetector.h"

namespace Transactions
{
class SimpleCategoryDetector : public CategoryDetector
{
public:
    SimpleCategoryDetector();
    ~SimpleCategoryDetector();

    bool detect(std::shared_ptr<Transaction> &transaction) const;
};
}

#endif // SIMPLECATEGORYDETECTOR_H
