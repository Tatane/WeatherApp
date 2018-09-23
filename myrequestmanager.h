#ifndef MYREQUESTMANAGER_H
#define MYREQUESTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include "myforecastweather.h"
#include "myweatherdata.h"
#include "myweathericon.h"

class MyWeatherIconRequest;

class MyRequestManager : public QObject
{
    Q_OBJECT

public:
    static MyRequestManager * getInstance();

    void getForecastWeather(int cityId);
    void getCurrentWeather(int cityId);
    void getIcon(const QString & iconId);

private:
    static MyRequestManager * mInstance;
    MyRequestManager();
    QNetworkAccessManager mNetworkAccesManager;

    MyWeatherData mCurrentWeather;
    MyForecastWeather mWeaterForecast;
    QPixmap mIconPixmap;

    QUrl constructUrlRequestCurrentWeather(int cityId);
    QUrl constructUrlRequestWeatherForecast(int cityId);
    QUrl constructUrlRequestIcon(QString iconId);

    QString constructUrlParameterApiKey() const;
    QString constructUrlParameterTemperatureUnit() const;

    const QString SERVER = "http://api.openweathermap.org";
    const QString REST_SERVICE = "data/2.5";
    const QString WEATHER_FORECAST_SERVICE = "forecast";
    const QString CURRENT_WEATHER_SERVICE = "weather";

private slots:
    void parseCurrentWeatherReply();
    void parseWeatherForecastReply();
    void iconReceived(MyWeatherIcon* weatherIcon);

signals:
    void currentWeatherReady(MyWeatherData*);
    void iconReady(MyWeatherIcon*);
    void weatherForecastReady(MyForecastWeather*);
};

#endif // MYREQUESTMANAGER_H
