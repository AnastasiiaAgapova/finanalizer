#ifndef ANALYZEDTRANSACTION_H
#define ANALYZEDTRANSACTION_H

#include <memory>

namespace Transactions
{
class Transaction;
}

namespace Calculation
{
enum AnomalyStatus
{
    Undefined,
    Normal,
    Anomalous
};

class AnalyzedTransaction
{
public:
    AnalyzedTransaction(const std::shared_ptr<Transactions::Transaction> &transaction);

    AnomalyStatus status() const;
    void setStatus(AnomalyStatus newStatus);

    double getScore() const;
    void setScore(double newScore);

    std::shared_ptr<Transactions::Transaction> transaction() const;

private:
    std::shared_ptr<Transactions::Transaction> _transaction;
    AnomalyStatus _status = Undefined;
    double score = 0.0;

};
}

#endif // ANALYZEDTRANSACTION_H
