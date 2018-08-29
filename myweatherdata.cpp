#include "myweatherdata.h"

MyWeatherData::MyWeatherData()
{

}

double MyWeatherData::getTemperature() const
{
    return mTemperature;
}

void MyWeatherData::setTemperature(double t)
{
    mTemperature = t;
}

QString MyWeatherData::getIconId() const
{
    return mIconId;
}

void MyWeatherData::setIconId(QString s)
{
    mIconId = s;
}


QString MyWeatherData::getCityName() const
{
    return mCityName;
}

void MyWeatherData::setCityName(QString cityName)
{
    mCityName = cityName;
}

QDateTime MyWeatherData::getDateTime() const
{
    return mDateTime;
}

void MyWeatherData::setDateTime(QDateTime dateTime)
{
    mDateTime = dateTime;
}
