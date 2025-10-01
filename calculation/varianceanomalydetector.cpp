#include "varianceanomalydetector.h"

#include "transactions/database.h"

namespace Calculation
{
VarianceAnomalyDetector::VarianceAnomalyDetector() {}

bool VarianceAnomalyDetector::analyze(const Transactions::Database *database)
{
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
                if (transaction->anomalyStatusSource() != Transactions::Transaction::UserDefined)
                {
                    const double z = (transaction->amount() - mu) / sigma;

                    transaction->setAnomalyStatus(std::abs(z) > _coefficient ? Transactions::Transaction::Anomalous : Transactions::Transaction::Normal);
                    transaction->setAnomalyStatusSource(Transactions::Transaction::Calculated);
                }
            }
        }
    }
    return true;
}

void VarianceAnomalyDetector::setCoefficient(double newCoefficient)
{
    _coefficient = newCoefficient;
}
}


