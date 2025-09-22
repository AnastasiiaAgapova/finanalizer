#include "madanomalydetector.h"

#include "transactions/database.h"
#include "analyzedtransaction.h"

namespace Calculation
{
MADAnomalyDetector::MADAnomalyDetector() {}

QVector<std::shared_ptr<AnalyzedTransaction>> MADAnomalyDetector::analyze(const Transactions::Database *database)
{
    QVector<std::shared_ptr<AnalyzedTransaction>> res;

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
                const double z_mad = 0.6745 * (transaction->amount() - median) / mad;

                if (std::abs(z_mad) > _coefficient)
                {
                    auto analyzedTransaction = std::make_shared<AnalyzedTransaction>(transaction);
                    analyzedTransaction->setStatus(Anomalous);
                    analyzedTransaction->setScore(z_mad);
                    res.append(analyzedTransaction);
                }
            }
        }
    }
    return res;
}

void MADAnomalyDetector::setCoefficient(double newCoefficient)
{
    _coefficient = newCoefficient;
}
}
