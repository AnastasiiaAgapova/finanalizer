#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>

class AppConfig
{
public:
    static AppConfig &instance();

    QString databasePath() const;
    void setDatabasePath(const QString &path);

    QString trainModelScriptPath() const;
    void setTrainModelScriptPath(const QString &path);

    QString aiModelPath() const;
    void setAiModelPath(const QString &name);

    QString transactionsForAiModelPath() const;
    void setTransactionsForAiModelPath(const QString &name);

    QString pythonPath() const;
    void setPythonPath(const QString pythonPath);

private:
    AppConfig();
    Q_DISABLE_COPY(AppConfig)

    QSettings _settings;
};

#endif // APPCONFIG_H
