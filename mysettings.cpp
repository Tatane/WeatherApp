#include "mysettings.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QSettings>

MySettings* MySettings::mInstance = nullptr;

MySettings *MySettings::getInstance()
{
    if (nullptr == mInstance)
    {
        mInstance = new MySettings;
    }
    return mInstance;
}

MySettings::Units MySettings::getUnitsFromString(QString s)
{
    if (s.compare("metric") == 0)
    {
        return Units::Metric;
    }
    else if (s.compare("imperial") == 0)
    {
        return Units::Imperial;
    }
    else
    {
        return Units::Standard;
    }
}

QString MySettings::getApiKey() const
{
    return mApiKey;
}

MySettings::MySettings()
    : mUnits(Units::Metric)
    , mApiKey("")
{
    QString settingsFileFullPath = qApp->applicationDirPath() + QDir::separator() + SETTINGS_FILE_NAME;
    readSettingsFile(settingsFileFullPath);
}

void MySettings::readSettingsFile(QString fullPathToSettingsFile)
{
    QSettings settings(fullPathToSettingsFile, QSettings::IniFormat);
    settings.beginGroup(GROUP_SETTINGS);

    if (settings.contains(KEY_API_KEY))
    {
         mApiKey = settings.value(KEY_API_KEY).toString();
    }
    else
    {
        settings.setValue(KEY_API_KEY, QVariant(""));
        //TODO : Message
    }

    if ( ! settings.contains(KEY_UNITS))
    {
        settings.setValue(KEY_UNITS, QVariant("metric"));
    }
    mUnits = getUnitsFromString(settings.value(KEY_UNITS).toString());


}

MySettings::Units MySettings::getUnits() const
{
    return mUnits;
}

void MySettings::setUnits(const MySettings::Units &units)
{
    mUnits = units;
}


