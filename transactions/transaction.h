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
        INVALID = -1,
        INCOME,
        OUTCOME
    };

    Transaction();

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    uint amount() const;
    void setAmount(uint newAmount);

    QString category() const;
    void setCategory(const QString &newCategory);

    QString description() const;
    void setDescription(const QString &newDescription);


    Type type() const;
    void setType(Type newType);

private:
    QDateTime _dateTime;
    uint _amount = 0; // in minimal units e.g. pence
    QString _category = 0;
    QString _description = 0;
    Type _type = INVALID;
};
}

#endif // TRANSACTION_H
