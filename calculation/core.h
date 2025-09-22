#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QVector>

namespace Transactions
{
class Database;
class Transaction;
}

namespace Calculation
{
class AnalyzedTransaction;
class AnomalyDetector;
class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject *parent);
    ~Core();

    void analyze(Transactions::Database *database);

    bool isAnomaly(const std::shared_ptr<Transactions::Transaction> &transaction);

signals:
    void analyzed();

private:
    AnomalyDetector *_detector;
    QVector<std::shared_ptr<AnalyzedTransaction>> _analyzedTransactions;
};
}

#endif // CORE_H
