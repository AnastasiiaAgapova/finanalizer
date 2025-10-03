#include "transaction.h"

namespace Transactions
{
Transaction::Transaction() {}

QDateTime Transaction::dateTime() const
{
    return _dateTime;
}

void Transaction::setDateTime(const QDateTime &newDateTime)
{
    _dateTime = newDateTime;
}

int Transaction::amount() const
{
    return _amount;
}

void Transaction::setAmount(int newAmount)
{
    _amount = newAmount;
}

QString Transaction::category() const
{
    return _category;
}

void Transaction::setCategory(const QString &newCategory)
{
    _category = newCategory;
}

QString Transaction::description() const
{
    return _description;
}

void Transaction::setDescription(const QString &newDescription)
{
    _description = newDescription;
}

Transaction::Type Transaction::type() const
{
    return _type;
}

void Transaction::setType(Type newType)
{
    _type = newType;
}

Transaction::AnomalyStatus Transaction::anomalyStatus() const
{
    return _anomalyStatus;
}

void Transaction::setAnomalyStatus(AnomalyStatus newStatus)
{
    _anomalyStatus = newStatus;
}

Transaction::AnomalyStatusSource Transaction::anomalyStatusSource() const
{
    return _anomalyStatusSource;
}

void Transaction::setAnomalyStatusSource(AnomalyStatusSource newAnomalyStatusSource)
{
    _anomalyStatusSource = newAnomalyStatusSource;
}

}
