#include "database.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

namespace Transactions
{

const char* Database::TRANSACTIONS_KEY = "transactions";
const char* Database::ID_KEY = "id";
const char* Database::DATE_TIME_KEY = "dateTime";
const char* Database::AMOUNT_KEY = "amount";
const char* Database::CATEGORY_KEY = "category";
const char* Database::DESCRIPTION_KEY = "description";
const char* Database::DATE_TIME_FORMAT = "dd.MM.yyyy";

Database::Database(QObject *parent) : QObject(parent) {}

Database::~Database()
{
    clearDatabase();
}

bool Database::save() const
{
    if (_fileName.isEmpty())
        return false;
    QFile file(_fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonArray transactionArray;
    for(const auto& transaction : _transactions)
    {
        QJsonObject transactionObject;
        transactionObject.insert(ID_KEY, QJsonValue::fromVariant(transaction->id()));
        transactionObject.insert(DATE_TIME_KEY, QJsonValue::fromVariant(transaction->dateTime().toString(DATE_TIME_FORMAT)));
        transactionObject.insert(AMOUNT_KEY, QJsonValue::fromVariant(transaction->amount()));
        transactionObject.insert(CATEGORY_KEY, QJsonValue::fromVariant(transaction->category()));
        transactionObject.insert(DESCRIPTION_KEY, QJsonValue::fromVariant(transaction->description()));

        transactionArray.append(QJsonValue(transactionObject));
    }
    QJsonObject databaseObject;
    databaseObject.insert(TRANSACTIONS_KEY, QJsonValue(transactionArray));

    file.write(QJsonDocument(databaseObject).toJson());
    file.close();

    return true;
}

bool Database::load()
{
    if (_fileName.isEmpty())
        return false;
    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(), &error);
    file.close();
    if (error.error != QJsonParseError::ParseError::NoError)
        return false;
    if (jsonDocument.isNull())
        return false;

    const QJsonArray transactionsArray = jsonDocument.object().value(TRANSACTIONS_KEY).toArray();
    if (transactionsArray.isEmpty())
        return false;
    clearDatabase();
    for (const auto value : transactionsArray)
    {
        const QJsonObject jsonObject = value.toObject();
        Transaction *transaction = new Transaction();
        transaction->setId(jsonObject.value(ID_KEY).toInt());
        transaction->setDateTime(QDateTime::fromString(jsonObject.value(DATE_TIME_KEY).toString(), DATE_TIME_FORMAT));
        transaction->setAmount(jsonObject.value(AMOUNT_KEY).toInt());
        transaction->setCategory(jsonObject.value(CATEGORY_KEY).toString());
        transaction->setDescription(jsonObject.value(DESCRIPTION_KEY).toString());
        _transactions.append(transaction);
    }
    emit changed();
    return true;

}

QString Database::fileName() const
{
    return _fileName;
}

void Database::setFileName(const QString &newFileName)
{
    _fileName = newFileName;
}

void Database::addTransaction(Transaction *transaction)
{
    transaction->setId(_transactions.isEmpty() ? 1 : (_transactions.last()->id() + 1));
    _transactions.append(transaction);
    emit changed();
}

int Database::size() const
{
    return _transactions.size();
}

QList<const Transaction *> Database::transactions() const
{
    QList<const Transaction*> res;
    for (const auto &transaction : _transactions)
        res.append(transaction);
    return res;
}

const Transaction *Database::transactionAt(int index) const
{
    if (index < 0 || index >= size())
        return nullptr;
    return _transactions.at(index);
}

QList<const Transaction *> Database::filterTransactions(const Filter *filter) const
{
    QList<const Transaction *> res;
    foreach (auto &transaction, _transactions)
        if (filter->isMatch(transaction))
            res.append(transaction);
    return res;
}

void Database::clearDatabase()
{
    qDeleteAll(_transactions);
    _transactions.clear();
    emit changed();
}
}
