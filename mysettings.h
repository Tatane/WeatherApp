#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QString>

class MySettings
{
public:
    static MySettings * getInstance();

    enum class Units
    {
        Standard,
        Metric,
        Imperial
    };



    Units getUnits() const;
    void setUnits(const Units &units);

    QString getApiKey() const;

private:
    MySettings();
    void readSettingsFile(QString fullPathToSettingsFile);
    Units getUnitsFromString(QString s);

    const QString SETTINGS_FILE_NAME = "settings.ini";
    const QString GROUP_SETTINGS = "settings";
    const QString KEY_API_KEY = "api_key";
    const QString KEY_UNITS = "units";

    static MySettings* mInstance;
    Units mUnits;

    QString mApiKey;
};

#endif // MYSETTINGS_H
