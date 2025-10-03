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

    uint getCategoryNum(const QString &category) const;

    QMap<QString, uint> categories() const;
    void setCategories(const QMap<QString, uint> &categories);

    static const uint InvalidCategoryNum;

signals:
    void changed();

protected:
    uint checkAndUpdateCategories(const QString &category);

private:
    QVector<std::shared_ptr<Transaction>> _transactions;
    QMap<QString, uint> _categories;
};

}

#endif // DATABASE_H
