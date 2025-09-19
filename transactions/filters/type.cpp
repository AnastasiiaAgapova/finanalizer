#include "type.h"

namespace Transactions
{
namespace Filters
{
    Type::Type(Transaction::Type type)
        : _type(type)
    {

    }

    bool Type::isMatch(const Transaction &transaction) const
    {
        return transaction.type() == _type;
    }
}
}
