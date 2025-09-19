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
    ~Category() override {}
    bool isMatch(const Transaction &transaction) const override;

private:
    QString _category;
};
}
}
#endif // CATEGORY_H
