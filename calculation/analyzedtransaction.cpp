#include "analyzedtransaction.h"

namespace Calculation
{
AnalyzedTransaction::AnalyzedTransaction(const std::shared_ptr<Transactions::Transaction> &transaction)
    : _transaction(transaction)
{}

AnomalyStatus AnalyzedTransaction::status() const
{
    return _status;
}

void AnalyzedTransaction::setStatus(AnomalyStatus newStatus)
{
    _status = newStatus;
}

double AnalyzedTransaction::getScore() const
{
    return score;
}

void AnalyzedTransaction::setScore(double newScore)
{
    score = newScore;
}

std::shared_ptr<Transactions::Transaction> AnalyzedTransaction::transaction() const
{
    return _transaction;
}
}
