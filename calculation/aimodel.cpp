#include "aimodel.h"

#include <QFileInfo>
#include <QProcess>
#include <QDebug>

#include "transactions/database.h"
#include "transactions/transaction.h"
#include "appconfig.h"

namespace Calculation
{
AiModel::AiModel(const QString &modelPath,
                 const QString &pythonScript,
                 const QString &dataPath)
    : _modelPath(QFileInfo(modelPath).absoluteFilePath()),
    _pythonScript(QFileInfo(pythonScript).absoluteFilePath()),
    _dataPath(QFileInfo(dataPath).absoluteFilePath()),
    _env(ORT_LOGGING_LEVEL_WARNING, "AiModel"),
    _session(nullptr)
{
    _sessionOptions.SetIntraOpNumThreads(1);
    _sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_BASIC);
}

bool AiModel::trainModel()
{
    QProcess process;
    QStringList args;
    args << _pythonScript
         << "--data" << _dataPath
         << "--output" << _modelPath;

    process.start(AppConfig::instance().pythonPath(), args);
    if (!process.waitForFinished(-1))
    {
        qWarning() << "Python training script failed to run.";
        qDebug() << process.readAllStandardOutput();
        return false;
    }
    int exitCode = process.exitCode();
    if (exitCode != 0)
    {
        qWarning() << "Training script error:" << process.readAllStandardError() << process.exitCode() << process.exitStatus();
        qDebug() << process.readAllStandardOutput();
        return false;
    }
    qDebug() << process.readAllStandardOutput();


    return true;
}

bool AiModel::loadModel()
{
    try
    {
        std::wstring onnxPath = _modelPath.toStdWString();
        _session = new Ort::Session(_env, onnxPath.c_str(), _sessionOptions);
    }
    catch (const Ort::Exception& e)
    {
        qWarning() << "Failed to load ONNX model:" << e.what();
        return false;
    }
    return true;
}

void AiModel::unloadModel()
{
    if (_session)
    {
        delete _session;
        _session = nullptr;
        qDebug() << "Model unloaded from memory.";
    }
    else
        qDebug() << "No model loaded.";
}

float AiModel::evaluateTransaction(const Transactions::Database *database, const std::shared_ptr<Transactions::Transaction> &transaction)
{
    if (!_session)
    {
        qWarning() << "Model not loaded!";
        return -1.0f;
    }
    // --- Подготовка входных данных ---
    std::vector<float> inputTensorValues = {static_cast<float>(database->getCategoryNum(transaction->category()))
                                            , static_cast<float>(abs(transaction->amount()))};
    std::vector<int64_t> inputShape = {1, 2};

    auto memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo,
        inputTensorValues.data(),
        inputTensorValues.size(),
        inputShape.data(),
        inputShape.size());

    Ort::AllocatorWithDefaultOptions allocator;

    // --- Получаем имена входа/выхода ---
    auto inputNamePtr = _session->GetInputNameAllocated(0, allocator);
    const char* inputName = inputNamePtr.get();

    auto outputNamePtr = _session->GetOutputNameAllocated(0, allocator);
    const char* outputName = outputNamePtr.get();

    const char* inputNames[] = {inputName};
    const char* outputNames[] = {outputName};

    auto outputTensors = _session->Run(
        Ort::RunOptions{nullptr},
        inputNames,
        &inputTensor,
        1,
        outputNames,
        1);

    float* outputArr = outputTensors.front().GetTensorMutableData<float>();
    float result = outputArr[0];

    return result; // например вероятность аномалии
}
}
