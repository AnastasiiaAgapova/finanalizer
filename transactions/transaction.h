#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDateTime>

namespace Transactions
{
class Transaction
{
public:
    Transaction();
    int id() const;
    void setId(int newId);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    int amount() const;
    void setAmount(int newAmount);

    QString category() const;
    void setCategory(const QString &newCategory);

    QString description() const;
    void setDescription(const QString &newDescription);

private:
    int _id; //is it needed?
    QDateTime _dateTime;
    int _amount; // in minimal units e.g. pence
    QString _category;
    QString _description;
};
}

#endif // TRANSACTION_H
