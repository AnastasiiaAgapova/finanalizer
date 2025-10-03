#include "database.h"



namespace Transactions
{

const uint Database::InvalidCategoryNum = std::numeric_limits<uint>().max();

Database::Database(QObject *parent) : QObject(parent) {}

Database::~Database()
{
    clearDatabase();
}

void Database::addTransaction(const std::shared_ptr<Transaction> &transaction)
{
    _transactions.append(transaction);
    checkAndUpdateCategories(transaction->category());
    sortDatabase();
    emit changed();
}

void Database::addTransactions(QVector<std::shared_ptr<Transaction>> transactions)
{
    _transactions.append(transactions);
    for (auto &transaction : transactions)
        checkAndUpdateCategories(transaction->category());
    sortDatabase();
    emit changed();
}

int Database::size() const
{
    return _transactions.size();
}

QVector<std::shared_ptr<Transaction>> Database::transactions() const
{
    return _transactions;
}

const std::shared_ptr<Transaction> &Database::transactionAt(int index) const
{
    return _transactions.at(index);
}

QMap<QString, QVector<std::shared_ptr<Transaction>>> Database::categorizedTransactions() const
{
    QMap<QString, QVector<std::shared_ptr<Transaction>>> res;
    for (auto &transaction : _transactions)
    {
        res[transaction->category()].append(transaction);
    }
    return res;

}

QVector<std::shared_ptr<Transaction>> Database::filterTransactions(const Filter *filter) const
{
    QVector<std::shared_ptr<Transaction>> res;
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
        return _transactions.first()->dateTime().date();
}

QDate Database::endDate() const
{
    if (_transactions.empty())
        return QDate();
    else
        return _transactions.last()->dateTime().date();
}

void Database::clearDatabase()
{
    _transactions.clear();
    emit changed();
}

void Database::sortDatabase()
{
    std::sort(_transactions.begin(), _transactions.end(), [](const std::shared_ptr<Transaction> &a, const std::shared_ptr<Transaction> &b){
        return a->dateTime() < b->dateTime();
    });
}

uint Database::getCategoryNum(const QString &category) const
{
    if (_categories.contains(category))
        return _categories[category];
    else
        return InvalidCategoryNum;
}

uint Database::checkAndUpdateCategories(const QString &category)
{
    if (!_categories.contains(category))
    {
        const auto values = _categories.values();
        _categories.insert(category, values.isEmpty() ? 1 : *(std::max_element(values.begin(), values.end())) + 1);

    }
    return _categories[category];
}

QMap<QString, uint> Database::categories() const
{
    return _categories;
}

void Database::setCategories(const QMap<QString, uint> &categories)
{
    _categories = categories;
}
}
