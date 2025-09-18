#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>

class AppConfig
{
public:
    static AppConfig &instance();

    QString databasePath() const;

    void setDatabasePath(const QString &path);

private:
    AppConfig();
    Q_DISABLE_COPY(AppConfig)

    QSettings _settings;
};

#endif // APPCONFIG_H
