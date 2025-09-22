#include "core.h"

#include "analyzedtransaction.h"
#include "madanomalydetector.h"

namespace Calculation
{
Core::Core(QObject *parent)
    : QObject(parent)
    , _detector(new MADAnomalyDetector())
{}

Core::~Core()
{
    delete _detector;
}

void Core::analyze(Transactions::Database *database)
{
    _analyzedTransactions = _detector->analyze(database);
    emit analyzed();
}

bool Core::isAnomaly(const std::shared_ptr<Transactions::Transaction> &transaction)
{
    for (auto &analyzedTransaction : _analyzedTransactions)
    {
        if (analyzedTransaction->transaction().get() == transaction.get()
            && analyzedTransaction->status() == Anomalous)
            return true;
    }
    return false;
}
}
