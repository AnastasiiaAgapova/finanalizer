#include "category.h"

namespace Transactions
{
namespace Filters
{
Category::Category(const QString &category)
    : _category(category)
{

}

bool Category::isMatch(const std::shared_ptr<Transaction> &transaction) const
{
    return transaction->category() == _category;
}
}
}
