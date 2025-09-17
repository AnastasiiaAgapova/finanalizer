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

    /**
     * Adds a transaction to the database.
     * The database takes ownership of the transaction pointer,
     * and will delete it when the database is cleared or destroyed.
     *
     * @param transaction Pointer to the transaction. Must not be deleted by the caller.
     */
    void addTransaction(Transaction *transactions);

    int size() const;

    QList<const Transaction *> transactions() const;
    const Transaction *transactionAt(int index) const;

    QList<const Transaction *> filterTransactions(const Filter *filter) const;

signals:
    void changed();

private:
    void clearDatabase();

private:
    static const char* TRANSACTIONS_KEY;
    static const char* ID_KEY;
    static const char* DATE_TIME_KEY;
    static const char* AMOUNT_KEY;
    static const char* CATEGORY_KEY;
    static const char* DESCRIPTION_KEY;
    static const char* DATE_TIME_FORMAT;


    QList<Transaction *> _transactions;
    QString _fileName;
};

}

#endif // DATABASE_H
