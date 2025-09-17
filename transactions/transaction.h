#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDateTime>

namespace Transactions
{
class Transaction
{
public:
    Transaction();

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    int amount() const;
    void setAmount(int newAmount);

    QString category() const;
    void setCategory(const QString &newCategory);

    QString description() const;
    void setDescription(const QString &newDescription);

private:
    QDateTime _dateTime;
    int _amount = 0; // in minimal units e.g. pence
    QString _category = 0;
    QString _description = 0;
};
}

#endif // TRANSACTION_H
