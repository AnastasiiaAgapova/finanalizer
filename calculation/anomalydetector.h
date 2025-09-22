#ifndef ANOMALYDETECTOR_H
#define ANOMALYDETECTOR_H

#include <QVector>

namespace Transactions
{
class Database;
}

namespace Calculation
{
class AnalyzedTransaction;
class AnomalyDetector
{
public:
    virtual ~AnomalyDetector() {};
    virtual QVector<std::shared_ptr<AnalyzedTransaction>> analyze(const Transactions::Database * database) = 0;
};
}
#endif // ANOMALYDETECTOR_H
