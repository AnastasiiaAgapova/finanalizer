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

    bool save() const;
    bool load();

    QString fileName() const;
    void setFileName(const QString &newFileName);

    void addTransaction(const Transaction &transaction);
    void addTransactions(QList<Transaction> transactions);

    int size() const;

    QList<Transaction> transactions() const;
    const Transaction &transactionAt(int index) const;

    QList<Transaction> filterTransactions(const Filter *filter) const;

    QDate startDate() const;
    QDate endDate() const;

signals:
    void changed();

private:
    void clearDatabase();
    void sortDatabase();

private:
    static const char* TRANSACTIONS_KEY;
    static const char* DATE_TIME_KEY;
    static const char* AMOUNT_KEY;
    static const char* CATEGORY_KEY;
    static const char* DESCRIPTION_KEY;
    static const char* DATE_TIME_FORMAT;


    QList<Transaction> _transactions;
    QString _fileName;
};

}

#endif // DATABASE_H
