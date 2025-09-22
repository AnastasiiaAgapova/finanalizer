#ifndef VARIANCEANOMALYDETECTOR_H
#define VARIANCEANOMALYDETECTOR_H

#include "anomalydetector.h"

namespace Calculation
{
class VarianceAnomalyDetector : public AnomalyDetector
{
public:
    VarianceAnomalyDetector();
    ~VarianceAnomalyDetector() override {};
    virtual QVector<std::shared_ptr<AnalyzedTransaction>> analyze(const Transactions::Database *database) override;

    void setCoefficient(double newCoefficient);

private:
    double _coefficient = 2.0;
};
}

#endif // VARIANCEANOMALYDETECTOR_H
