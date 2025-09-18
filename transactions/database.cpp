#include "database.h"



namespace Transactions
{



Database::Database(QObject *parent) : QObject(parent) {}

Database::~Database()
{
    clearDatabase();
}

void Database::addTransaction(const Transaction &transaction)
{
    _transactions.append(transaction);
    sortDatabase();
    emit changed();
}

void Database::addTransactions(QList<Transaction> transactions)
{
    _transactions.append(transactions);
    sortDatabase();
    emit changed();
}

int Database::size() const
{
    return _transactions.size();
}

QList<Transaction> Database::transactions() const
{
    return _transactions;
}

const Transaction &Database::transactionAt(int index) const
{
    return _transactions.at(index);
}

QList<Transaction> Database::filterTransactions(const Filter *filter) const
{
    QList<Transaction> res;
    foreach (auto &transaction, _transactions)
        if (filter->isMatch(transaction))
            res.append(transaction);
    return res;
}

QDate Database::startDate() const
{
    if (_transactions.empty())
        return QDate();
    else
        return _transactions.first().dateTime().date();
}

QDate Database::endDate() const
{
    if (_transactions.empty())
        return QDate();
    else
        return _transactions.last().dateTime().date();
}

void Database::clearDatabase()
{
    _transactions.clear();
    emit changed();
}

void Database::sortDatabase()
{
    std::sort(_transactions.begin(), _transactions.end(), [](const Transaction &a, const Transaction &b){
        return a.dateTime() < b.dateTime();
    });
}
}
