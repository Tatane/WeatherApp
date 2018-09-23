#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QString>

#include <QLocale>

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

    QLocale getLocale() const;
    void setLocale(const QLocale &locale);

private:
    MySettings();
    void readSettingsFile(QString fullPathToSettingsFile);
    Units getUnitsFromString(QString s);
    QLocale getLocaleFromString(QString s);

    const QString SETTINGS_FILE_NAME = "settings.ini";
    const QString GROUP_SETTINGS = "settings";
    const QString KEY_API_KEY = "api_key";

    const QString KEY_UNITS = "units";
    const QString VALUE_UNITS_METRIC = "metric";
    const QString VALUE_UNITS_IMPERIAL = "imperial";

    const QString KEY_LANGUAGE = "language";
    const QString VALUE_LANGUAGE_ENGLISH = "english";
    const QString VALUE_LANGUAGE_FRENCH = "french";

    static MySettings* mInstance;
    Units mUnits;

    QString mApiKey;
    QLocale mLocale;
};

#endif // MYSETTINGS_H
