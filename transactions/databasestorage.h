#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H

#include <QString>

namespace Transactions
{
class Database;
class DatabaseStorage
{
public:
    DatabaseStorage();

    bool save(const Database *database, const QString &fileName) const;
    bool load(Database *database, const QString &fileName) const;

private:
    static const char* TRANSACTIONS_KEY;
    static const char* DATE_TIME_KEY;
    static const char* AMOUNT_KEY;
    static const char* CATEGORY_KEY;
    static const char* DESCRIPTION_KEY;
    static const char* TYPE_KEY;

    static const char* DATE_TIME_FORMAT;

};
}

#endif // DATABASESTORAGE_H
