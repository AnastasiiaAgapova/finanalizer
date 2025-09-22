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

    void addTransaction(const std::shared_ptr<Transaction> &transaction);
    void addTransactions(QVector<std::shared_ptr<Transaction>> transactions);

    int size() const;

    QVector<std::shared_ptr<Transaction>> transactions() const;
    const std::shared_ptr<Transaction> &transactionAt(int index) const;
    QMap<QString, QVector<std::shared_ptr<Transaction>>> categorizedTransactions() const;

    QVector<std::shared_ptr<Transaction>> filterTransactions(const Filter *filter) const;

    QDate startDate() const;
    QDate endDate() const;

    void clearDatabase();
    void sortDatabase();

signals:
    void changed();

private:
    QVector<std::shared_ptr<Transaction>> _transactions;
};

}

#endif // DATABASE_H
