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

AppConfig::AppConfig()
    :_settings("config.ini", QSettings::IniFormat)
{

}
