#ifndef COMPLEX_H
#define COMPLEX_H

#include "transactions/filter.h"

namespace Transactions
{
namespace Filters
{
class Complex : public Filter
{
public:
    Complex(QList<std::shared_ptr<Filter>> filters);
    ~Complex() override {}

    bool isMatch(const Transaction &transaction) const override;

private:
    QList<std::shared_ptr<Filter>> _filters;
};
}
}
#endif // COMPLEX_H
