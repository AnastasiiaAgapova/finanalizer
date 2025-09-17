#ifndef CATEGORY_H
#define CATEGORY_H

#include "transactions/filter.h"

namespace Transactions
{
namespace Filters
{
class Category : public Filter
{
public:
    Category(const QString &category);

    virtual bool isMatch(const Transaction &transaction) const;

private:
    QString _category;
};
}
}
#endif // CATEGORY_H
