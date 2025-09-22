#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QString>


namespace Transactions
{
class Transaction;
class Connector
{
public:
    virtual ~Connector() {};
    virtual QVector<std::shared_ptr<Transaction>> load(const QString &connectionString) const = 0;
};
}
#endif // CONNECTOR_H
