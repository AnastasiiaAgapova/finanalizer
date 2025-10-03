#ifndef AIMODEL_H
#define AIMODEL_H

#include <QString>

#include <onnxruntime_cxx_api.h>

namespace Transactions
{
class Database;
class Transaction;
}

namespace Calculation
{
class AiModel
{
public:
    explicit AiModel(const QString &modelPath,
                     const QString &pythonScript,
                     const QString &dataPath);

    bool trainModel();
    bool loadModel();
    void unloadModel();
    float evaluateTransaction(const Transactions::Database *database, const std::shared_ptr<Transactions::Transaction> &transaction);

private:
    QString _modelPath;
    QString _pythonScript;
    QString _dataPath;

    Ort::Env _env;
    Ort::Session* _session;
    Ort::SessionOptions _sessionOptions;
};

}

#endif // AIMODEL_H
