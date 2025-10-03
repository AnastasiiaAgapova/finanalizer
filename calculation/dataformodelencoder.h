#ifndef DATAFORMODELENCODER_H
#define DATAFORMODELENCODER_H

#include <QVector>

namespace Transactions
{
class Database;
class Transaction;
}

namespace Calculation
{
class DataForModelEncoder
{
public:
    DataForModelEncoder();

    bool save(Transactions::Database *database,
              const QVector<std::shared_ptr<Transactions::Transaction>> &transactions,
              const QString &filePath) const;
};
}
#endif // DATAFORMODELENCODER_H
