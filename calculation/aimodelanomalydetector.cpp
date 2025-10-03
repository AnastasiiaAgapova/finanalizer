#include "aimodelanomalydetector.h"

#include "aimodel.h"
#include "transactions/database.h"
#include "transactions/transaction.h"

namespace Calculation
{
AiModelAnomalyDetector::AiModelAnomalyDetector(const std::shared_ptr<AiModel> &model)
    : _model(model)
{

}

AiModelAnomalyDetector::~AiModelAnomalyDetector()
{

}

bool AiModelAnomalyDetector::analyze(const Transactions::Database *database)
{
    if (_model && _model->loadModel())
    {
        for (auto &transaction : database->transactions())
        {
            if (transaction->anomalyStatusSource() != Transactions::Transaction::UserDefined)
            {
                auto prediction = _model->evaluateTransaction(database, transaction);
                if (prediction >= 0.0f)
                {
                    transaction->setAnomalyStatusSource(Transactions::Transaction::Calculated);
                    transaction->setAnomalyStatus(std::round(prediction) ? Transactions::Transaction::Anomalous : Transactions::Transaction::Normal);
                }
            }
        }
        _model->unloadModel();
        return true;
    }
    else
        return false;
}
}
