#include "dataformodelencoder.h"

#include <QFile>
#include <QTextStream>

#include "transactions/database.h"
#include "transactions/transaction.h"

namespace Calculation
{
DataForModelEncoder::DataForModelEncoder() {}

bool DataForModelEncoder::save(Transactions::Database *database,
                               const QVector<std::shared_ptr<Transactions::Transaction>> &transactions,
                               const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QTextStream stream(&file);
    stream << "CategoryHash,Amount,IsAnomaly\n";
    stream.flush();
    for(auto &transaction : transactions)
    {
        stream << database->getCategoryNum(transaction->category()) << ","
               << abs(transaction->amount()) << ","
               << (transaction->anomalyStatus() == Transactions::Transaction::Anomalous ? 1 : 0)
               << "\n";
        stream.flush();
    }
    file.close();
    return true;
}
}
