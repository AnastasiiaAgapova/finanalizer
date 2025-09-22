#ifndef MADANOMALYDETECTOR_H
#define MADANOMALYDETECTOR_H

#include "anomalydetector.h"

namespace Calculation
{
class MADAnomalyDetector : public AnomalyDetector
{
public:
    MADAnomalyDetector();
    ~MADAnomalyDetector() override {};
    virtual QVector<std::shared_ptr<AnalyzedTransaction>> analyze(const Transactions::Database *database) override;

    void setCoefficient(double newCoefficient);

private:
    double _coefficient = 3.5;
};
}

#endif // MADANOMALYDETECTOR_H
