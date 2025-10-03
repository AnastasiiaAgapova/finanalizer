#ifndef AIMODELANOMALYDETECTOR_H
#define AIMODELANOMALYDETECTOR_H

#include "anomalydetector.h"

namespace Calculation
{
class AiModel;
class AiModelAnomalyDetector : public AnomalyDetector
{
public:
    AiModelAnomalyDetector(const std::shared_ptr<AiModel> &model);
    virtual ~AiModelAnomalyDetector() override;
    virtual bool analyze(const Transactions::Database *database) override;

private:
    std::shared_ptr<AiModel> _model;
};
}

#endif // AIMODELANOMALYDETECTOR_H
