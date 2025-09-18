#ifndef DATABASE_H
#define DATABASE_H

#include <QScopedPointer>

#include "transaction.h"
#include "filter.h"

namespace Transactions
{
class Database : public QObject
{
    Q_OBJECT
public:
    Database(QObject *parent = nullptr);
    ~Database();

    void addTransaction(const Transaction &transaction);
    void addTransactions(QList<Transaction> transactions);

    int size() const;

    QList<Transaction> transactions() const;
    const Transaction &transactionAt(int index) const;

    QList<Transaction> filterTransactions(const Filter *filter) const;

    QDate startDate() const;
    QDate endDate() const;

    void clearDatabase();
    void sortDatabase();

signals:
    void changed();

private:
    QList<Transaction> _transactions;
};

}

#endif // DATABASE_H
