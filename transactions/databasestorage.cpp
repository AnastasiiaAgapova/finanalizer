#include "databasestorage.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include "database.h"

namespace Transactions
{
const char* DatabaseStorage::TRANSACTIONS_KEY = "transactions";
const char* DatabaseStorage::DATE_TIME_KEY = "dateTime";
const char* DatabaseStorage::AMOUNT_KEY = "amount";
const char* DatabaseStorage::CATEGORY_KEY = "category";
const char* DatabaseStorage::DESCRIPTION_KEY = "description";
const char* DatabaseStorage::TYPE_KEY = "type";
const char* DatabaseStorage::DATE_TIME_FORMAT = "dd.MM.yyyy";

static const char* INVALID_TYPE = "Invalid";
static const char* INCOME_TYPE = "Income";
static const char* OUTCOME_TYPE = "Outcome";

QString transactionTypeToString(const Transaction::Type &type)
{
    switch (type)
    {
    case Transaction::INVALID:
        return INVALID_TYPE;
        break;
    case Transaction::INCOME:
        return INCOME_TYPE;
        break;
    case Transaction::OUTCOME:
        return OUTCOME_TYPE;
        break;
    }
    return QString();
}

Transaction::Type stringToTransactionType(const QString &type)
{
    if (type == INCOME_TYPE)
    {
        return Transaction::INCOME;
    }
    else if (type == OUTCOME_TYPE)
    {
        return Transaction::OUTCOME;
    }
    return Transaction::INVALID;
}

DatabaseStorage::DatabaseStorage() {}

bool DatabaseStorage::save(const Database *database, const QString &fileName) const
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonArray transactionArray;
    auto transactions = database->transactions();
    for(const auto &transaction : transactions)
    {
        QJsonObject transactionObject;
        transactionObject.insert(DATE_TIME_KEY, QJsonValue::fromVariant(transaction->dateTime().toString(DATE_TIME_FORMAT)));
        transactionObject.insert(AMOUNT_KEY, QJsonValue::fromVariant(transaction->amount()));
        transactionObject.insert(CATEGORY_KEY, QJsonValue::fromVariant(transaction->category()));
        transactionObject.insert(DESCRIPTION_KEY, QJsonValue::fromVariant(transaction->description()));
        transactionObject.insert(TYPE_KEY, QJsonValue::fromVariant(transactionTypeToString(transaction->type())));

        transactionArray.append(QJsonValue(transactionObject));
    }
    QJsonObject databaseObject;
    databaseObject.insert(TRANSACTIONS_KEY, QJsonValue(transactionArray));

    file.write(QJsonDocument(databaseObject).toJson());
    file.close();

    return true;
}

bool DatabaseStorage::load(Database *database, const QString &fileName) const
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
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
    database->clearDatabase();
    QVector<std::shared_ptr<Transaction>> transactions;
    for (const auto value : transactionsArray)
    {
        const QJsonObject jsonObject = value.toObject();
        auto transaction = std::make_shared<Transaction>();
        transaction->setDateTime(QDateTime::fromString(jsonObject.value(DATE_TIME_KEY).toString(), DATE_TIME_FORMAT));
        transaction->setAmount(jsonObject.value(AMOUNT_KEY).toVariant().toUInt());
        transaction->setCategory(jsonObject.value(CATEGORY_KEY).toString());
        transaction->setDescription(jsonObject.value(DESCRIPTION_KEY).toString());
        transaction->setType(stringToTransactionType(jsonObject.value(TYPE_KEY).toString()));
        transactions.append(transaction);
    }
    database->addTransactions(transactions);
    return true;
}
}
