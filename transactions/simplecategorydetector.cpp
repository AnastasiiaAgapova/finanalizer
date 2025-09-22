#include "simplecategorydetector.h"

namespace Transactions
{
    SimpleCategoryDetector::SimpleCategoryDetector()
    {

    }

    SimpleCategoryDetector::~SimpleCategoryDetector()
    {

    }

    bool SimpleCategoryDetector::detect(std::shared_ptr<Transaction> &transaction) const
    {
        if (transaction->category().isEmpty() && !transaction->description().isEmpty())
        {
            transaction->setCategory(transaction->description());
            return true;
        }
        return false;
    }

}
