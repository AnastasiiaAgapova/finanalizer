#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QString>

#include "transaction.h"

namespace Transactions
{
class Connector
{
public:
    virtual ~Connector() {};
    virtual QList<Transaction> load(const QString &connectionString) const = 0;
};
}
#endif // CONNECTOR_H
