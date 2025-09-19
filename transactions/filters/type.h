#ifndef TYPE_H
#define TYPE_H

#include "transactions/filter.h"

namespace Transactions
{
namespace Filters
{
class Type : public Filter
{
public:
    Type(Transaction::Type type);

    virtual ~Type() {}

    virtual bool isMatch(const Transaction &transaction) const;

private:
    Transaction::Type _type;
};
}
}
#endif // TYPE_H
