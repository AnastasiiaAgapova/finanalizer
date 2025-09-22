#include "varianceanomalydetector.h"

#include "transactions/database.h"
#include "analyzedtransaction.h"

namespace Calculation
{
VarianceAnomalyDetector::VarianceAnomalyDetector() {}

QVector<std::shared_ptr<AnalyzedTransaction>> VarianceAnomalyDetector::analyze(const Transactions::Database *database)
{
    QVector<std::shared_ptr<AnalyzedTransaction>> res;

    auto categorizedTransactions = database->categorizedTransactions();
    for (auto it = categorizedTransactions.begin(); it != categorizedTransactions.end(); ++it)
    {
        const auto &transactions = it.value();
        const int count = transactions.size();
        double sum = 0.0;
        for (auto &transaction : transactions)
            sum += transaction->amount();

        const double mu = sum / count;

        double sqrSum = 0.0;
        for (auto &transaction : transactions)
            sqrSum += pow(transaction->amount() - mu, 2);
        const double sigma = sqrt(sqrSum / count);
        if (sigma != 0.0)
        {
            for (auto &transaction : transactions)
            {
                const double z = (transaction->amount() - mu) / sigma;
                if (abs(z) > _coefficient)
                {
                    auto analyzedTransaction = std::make_shared<AnalyzedTransaction>(transaction);
                    analyzedTransaction->setStatus(Anomalous);
                    analyzedTransaction->setScore(z);
                    res.append(analyzedTransaction);
                }
            }
        }
    }
    return res;
}

void VarianceAnomalyDetector::setCoefficient(double newCoefficient)
{
    _coefficient = newCoefficient;
}
}


