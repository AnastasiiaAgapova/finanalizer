#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDateTime>

namespace Transactions
{
class Transaction
{
public:
    enum Type
    {
        Invalid = -1,
        Income,
        Outcome
    };

    enum AnomalyStatusSource
    {
        NotDefined,
        Calculated,
        UserDefined
    };

    enum AnomalyStatus
    {
        Undefined,
        Normal,
        Anomalous
    };

    Transaction();

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    int amount() const;
    void setAmount(int newAmount);

    QString category() const;
    void setCategory(const QString &newCategory);

    QString description() const;
    void setDescription(const QString &newDescription);


    Type type() const;
    void setType(Type newType);

    AnomalyStatus anomalyStatus() const;
    void setAnomalyStatus(AnomalyStatus newStatus);

    AnomalyStatusSource anomalyStatusSource() const;
    void setAnomalyStatusSource(AnomalyStatusSource newAnomalyStatusSource);

private:
    QDateTime _dateTime;
    int _amount = 0; // in minimal units e.g. pence
    QString _category;
    QString _description;
    Type _type = Invalid;

    AnomalyStatusSource _anomalyStatusSource = NotDefined;
    AnomalyStatus _anomalyStatus = Undefined;
};
}

#endif // TRANSACTION_H
