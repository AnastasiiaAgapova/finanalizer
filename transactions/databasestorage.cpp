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
const char* DatabaseStorage::ANOMALY_STATUS_KEY = "anomalyStatus";
const char* DatabaseStorage::ANOMALY_STATUS_SOURCE_KEY = "anomalyStatusSource";
const char* DatabaseStorage::DATE_TIME_FORMAT = "dd.MM.yyyy";

const char* DatabaseStorage::CATEGORIES_KEY = "Categories";
const char* DatabaseStorage::CATEGORY_NAME_KEY = "Name";
const char* DatabaseStorage::CATEGORY_NUM_KEY = "Num";

static const char* INVALID_TYPE = "Invalid";
static const char* INCOME_TYPE = "Income";
static const char* OUTCOME_TYPE = "Outcome";

static const char* UNDEFINED_STATUS = "Undefined";
static const char* ANOMALOUS_STATUS = "Anomalous";
static const char* NORMAL_STATUS = "Normal";
static const char* UNDEFINED_SOURCE = "Undefined";
static const char* CALCULATED_SOURCE = "Calculated";
static const char* USER_DEFINED_SOURCE = "User defined";

QString transactionTypeToString(const Transaction::Type &type)
{
    switch (type)
    {
    case Transaction::Invalid:
        return INVALID_TYPE;
    case Transaction::Income:
        return INCOME_TYPE;
    case Transaction::Outcome:
        return OUTCOME_TYPE;
    }
    return QString();
}

Transaction::Type stringToTransactionType(const QString &type)
{
    if (type == INCOME_TYPE)
    {
        return Transaction::Income;
    }
    else if (type == OUTCOME_TYPE)
    {
        return Transaction::Outcome;
    }
    return Transaction::Invalid;
}

QString anomalyStatusToString(const Transaction::AnomalyStatus &anomalyStatus)
{
    switch (anomalyStatus)
    {
    case Transaction::Undefined:
        return UNDEFINED_STATUS;
    case Transaction::Normal:
        return NORMAL_STATUS;
    case Transaction::Anomalous:
        return ANOMALOUS_STATUS;
    }
    return QString();
}

Transaction::AnomalyStatus stringToAnomalyStatus(const QString &type)
{
    if (type == ANOMALOUS_STATUS)
    {
        return Transaction::Anomalous;
    }
    else if (type == NORMAL_STATUS)
    {
        return Transaction::Normal;
    }
    return Transaction::Undefined;
}

QString anomalyStatusSourceToString(const Transaction::AnomalyStatusSource &source)
{
    switch (source)
    {
    case Transaction::NotDefined:
        return UNDEFINED_SOURCE;
    case Transaction::Calculated:
        return CALCULATED_SOURCE;
    case Transaction::UserDefined:
        return USER_DEFINED_SOURCE;
    }
    return QString();
}

Transaction::AnomalyStatusSource stringToAnomalyStatusSource(const QString &type)
{
    if (type == CALCULATED_SOURCE)
    {
        return Transaction::Calculated;
    }
    else if (type == USER_DEFINED_SOURCE)
    {
        return Transaction::UserDefined;
    }
    return Transaction::NotDefined;
}

DatabaseStorage::DatabaseStorage() {}

bool DatabaseStorage::save(const Database *database, const QString &fileName) const
{
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonObject databaseObject;

    QJsonArray categoriesArray;
    const auto categories = database->categories();
    for (auto it = categories.constBegin(); it != categories.constEnd(); ++it)
    {
        QJsonObject categoryObject;
        categoryObject.insert(CATEGORY_NAME_KEY, QJsonValue::fromVariant(it.key()));
        categoryObject.insert(CATEGORY_NUM_KEY, QJsonValue::fromVariant(it.value()));

        categoriesArray.append(categoryObject);
    }

    databaseObject.insert(CATEGORIES_KEY, QJsonValue(categoriesArray));

    QJsonArray transactionArray;
    const auto transactions = database->transactions();
    for(const auto &transaction : transactions)
    {
        QJsonObject transactionObject;
        transactionObject.insert(DATE_TIME_KEY, QJsonValue::fromVariant(transaction->dateTime().toString(DATE_TIME_FORMAT)));
        transactionObject.insert(AMOUNT_KEY, QJsonValue::fromVariant(transaction->amount()));
        transactionObject.insert(CATEGORY_KEY, QJsonValue::fromVariant(transaction->category()));
        transactionObject.insert(DESCRIPTION_KEY, QJsonValue::fromVariant(transaction->description()));
        transactionObject.insert(TYPE_KEY, QJsonValue::fromVariant(transactionTypeToString(transaction->type())));
        transactionObject.insert(ANOMALY_STATUS_KEY, QJsonValue::fromVariant(anomalyStatusToString(transaction->anomalyStatus())));
        transactionObject.insert(ANOMALY_STATUS_SOURCE_KEY, QJsonValue::fromVariant(anomalyStatusSourceToString(transaction->anomalyStatusSource())));

        transactionArray.append(QJsonValue(transactionObject));
    }

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

    const QJsonArray categoriesArray = jsonDocument.object().value(CATEGORIES_KEY).toArray();
    const QJsonArray transactionsArray = jsonDocument.object().value(TRANSACTIONS_KEY).toArray();
    if (transactionsArray.isEmpty())
        return false;
    database->clearDatabase();

    QMap<QString, uint> categories;
    for (const auto value : categoriesArray)
    {
        const QJsonObject jsonObject = value.toObject();
        categories.insert(jsonObject.value(CATEGORY_NAME_KEY).toString(), static_cast<uint>(jsonObject.value(CATEGORY_NUM_KEY).toInt()));
    }
    database->setCategories(categories);

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
        transaction->setAnomalyStatus(stringToAnomalyStatus(jsonObject.value(ANOMALY_STATUS_KEY).toString()));
        transaction->setAnomalyStatusSource(stringToAnomalyStatusSource(jsonObject.value(ANOMALY_STATUS_SOURCE_KEY).toString()));
        transactions.append(transaction);
    }
    database->addTransactions(transactions);
    return true;
}
}
