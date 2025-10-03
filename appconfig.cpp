#include "appconfig.h"


AppConfig &AppConfig::instance()
{
    static AppConfig _instance;
    return _instance;
}

QString AppConfig::databasePath() const
{
    return _settings.value("Database/Path", "database.json").toString();
}

void AppConfig::setDatabasePath(const QString &path)
{
    _settings.setValue("Database/Path", path);
}

QString AppConfig::trainModelScriptPath() const
{
    return _settings.value("AiModel/ScriptPath", "../../python/create_model.py").toString();
}

void AppConfig::setTrainModelScriptPath(const QString &path)
{
    _settings.setValue("AiModel/ScriptPath", path);
}

QString AppConfig::aiModelPath() const
{
    return _settings.value("AiModel/Path", "anomaly_model.onnx").toString();
}

void AppConfig::setAiModelPath(const QString &name)
{
    _settings.setValue("AiModel/Path", name);
}

QString AppConfig::transactionsForAiModelPath() const
{
    return _settings.value("AiModel/TransactionsPath", "transactions.csv").toString();
}

void AppConfig::setTransactionsForAiModelPath(const QString &name)
{
    _settings.setValue("AiModel/TransactionsPath", name);
}

QString AppConfig::pythonPath() const
{
    return _settings.value("PythonPath", "C:\\Users\\aagp\\AppData\\Local\\Programs\\Python\\Python313\\python.exe").toString();
}

void AppConfig::setPythonPath(const QString pythonPath)
{
    _settings.setValue("PythonPath", pythonPath);
}

AppConfig::AppConfig()
    :_settings("config.ini", QSettings::IniFormat)
{

}
