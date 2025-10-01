#include "madanomalydetector.h"

#include "transactions/database.h"

namespace Calculation
{
MADAnomalyDetector::MADAnomalyDetector() {}

bool MADAnomalyDetector::analyze(const Transactions::Database *database)
{
    auto categorizedTransactions = database->categorizedTransactions();
    for (auto it = categorizedTransactions.begin(); it != categorizedTransactions.end(); ++it)
    {
        const auto &transactions = it.value();
        const int count = transactions.size();
        if (count == 0)
            continue;

        // Собираем суммы в вектор
        QVector<int> amounts;
        amounts.reserve(count);
        for (auto &transaction : transactions)
            amounts.append(transaction->amount());

        // Сортируем для медианы
        std::sort(amounts.begin(), amounts.end());
        double median;
        if (count % 2 == 0)
            median = (amounts[count/2 - 1] + amounts[count/2]) / 2.0;
        else
            median = amounts[count/2];

        // Считаем абсолютные отклонения
        QVector<double> deviations;
        deviations.reserve(count);
        for (auto &val : amounts)
            deviations.append(std::abs(val - median));

        // Сортируем и считаем MAD
        std::sort(deviations.begin(), deviations.end());
        double mad;
        if (count % 2 == 0)
            mad = (deviations[count/2 - 1] + deviations[count/2]) / 2.0;
        else
            mad = deviations[count/2];


        if (mad > 0.0)
        {
            for (auto &transaction : transactions)
            {
                if (transaction->anomalyStatusSource() != Transactions::Transaction::UserDefined)
                {
                    const double z_mad = 0.6745 * (transaction->amount() - median) / mad;

                    transaction->setAnomalyStatus(std::abs(z_mad) > _coefficient ? Transactions::Transaction::Anomalous : Transactions::Transaction::Normal);
                    transaction->setAnomalyStatusSource(Transactions::Transaction::Calculated);
                }
            }
        }
    }
    return true;
}

void MADAnomalyDetector::setCoefficient(double newCoefficient)
{
    _coefficient = newCoefficient;
}
}
