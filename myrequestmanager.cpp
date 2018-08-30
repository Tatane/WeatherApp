#include "myrequestmanager.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include "myweathericon.h"

#include "myweathericonrequest.h"
#include "mysettings.h"

MyRequestManager* MyRequestManager::mInstance = nullptr;

MyRequestManager *MyRequestManager::getInstance()
{
    if (nullptr == mInstance)
    {
        mInstance = new MyRequestManager;
    }

    return mInstance;
}

void MyRequestManager::getForecastWeather(int cityId)
{
    QNetworkReply * reply = mNetworkAccesManager.get(QNetworkRequest(constructUrlRequestWeatherForecast(cityId)));
    connect(reply, SIGNAL(finished()), this, SLOT(parseWeatherForecastReply()));
}

void MyRequestManager::getCurrentWeather(int cityId)
{
    QNetworkReply * reply = mNetworkAccesManager.get(QNetworkRequest(constructUrlRequestCurrentWeather(cityId)) );
    connect(reply, SIGNAL(finished()), this, SLOT(parseCurrentWeatherReply()));
}

MyWeatherIconRequest * MyRequestManager::getIcon(const QString &iconId)
{
    QNetworkReply * reply = mNetworkAccesManager.get(QNetworkRequest(constructUrlRequestIcon(iconId)));

    MyWeatherIconRequest * weatherIconRequest = new MyWeatherIconRequest(iconId, reply);
    // TODO : Store this object in a container until it's finished.

    connect(weatherIconRequest, SIGNAL(iconReady(MyWeatherIcon*)), this, SIGNAL(iconReady(MyWeatherIcon*)));
    // can I connect this SIGNAL directly to a this->SIGNAL ?

    // ? mapper la reply avec id
    //mMapIconBeingDownloaded[reply] = iconId;
    //connect(reply, SIGNAL(finished()), this, SLOT(parseIconReply()));

    return weatherIconRequest;
}

MyRequestManager::MyRequestManager()
{

}

QUrl MyRequestManager::constructUrlRequestCurrentWeather(int cityId)
{
    return QUrl(SERVER + "/" + REST_SERVICE + "/" + CURRENT_WEATHER_SERVICE + "?id=" + QString::number(cityId) + constructUrlParameterApiKey() + constructUrlParameterTemperatureUnit());
}

QUrl MyRequestManager::constructUrlRequestWeatherForecast(int cityId)
{
    return QUrl(SERVER + "/" + REST_SERVICE + "/" + WEATHER_FORECAST_SERVICE + "?id=" + QString::number(cityId) + constructUrlParameterApiKey() + constructUrlParameterTemperatureUnit());
}

QUrl MyRequestManager::constructUrlRequestIcon(QString iconId)
{
    return QUrl(SERVER + "/img/w/" + iconId + ".png");
}

QString MyRequestManager::constructUrlParameterApiKey() const
{
    QString ret = "";
    QString apiKey = MySettings::getInstance()->getApiKey();
    if ( ! apiKey.isEmpty())
    {
        return "&APPID=" + apiKey;
    }

    return ret;
}

QString MyRequestManager::constructUrlParameterTemperatureUnit() const
{
    QString ret = "";
    switch (MySettings::getInstance()->getUnits()) {
    case MySettings::Units::Standard:
        ret = "&units=standard";
    case MySettings::Units::Metric:
        ret = "&units=metric";
        break;
    case MySettings::Units::Imperial:
        ret = "&units=imperial";
        break;
    default:
        ret = "";
        break;
    }
    return ret;
}

void MyRequestManager::parseCurrentWeatherReply()
{
    QNetworkReply * reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    if (reply != nullptr)
    {
        // Parse JSON
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll(), &parseError);

        if (! doc.isNull())
        {
            // Get data from the JSON document :
            QJsonObject obj = doc.object();
            if (! obj.isEmpty()) // should be an Object
            {
                // Temperature
                if (obj.contains("main"))
                {
                    QJsonValue temperature = obj["main"].toObject()["temp"].toDouble();
                    mCurrentWeather.setTemperature(temperature.toDouble());
                }

                // Icon id
                if (obj.contains("weather") && obj["weather"].isArray())
                {
                    QJsonValue icon = obj["weather"].toArray()[0].toObject()["icon"];
                    mCurrentWeather.setIconId(icon.toString());
                }

                // City name
                if(obj.contains("name"))
                {
                    QJsonValue cityName = obj["name"];
                    mCurrentWeather.setCityName(cityName.toString());
                }

                // Date Time
                if (obj.contains("dt"))
                {
                    QJsonValue dateTime = obj["dt"];
                    mCurrentWeather.setDateTime(QDateTime::fromSecsSinceEpoch(dateTime.toInt()));
                }

                currentWeatherReady(&mCurrentWeather);
            }
        }
        else
        {
            qDebug()<<parseError.errorString();
        }
    }
}

void MyRequestManager::parseWeatherForecastReply()
{
    QNetworkReply * reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    if (reply != nullptr)
    {
        // Parse JSON
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll(), &parseError);

        if (! doc.isNull())
        {
            // Get data from the JSON document :
            QJsonObject obj = doc.object();

            if (! obj.isEmpty() && obj.contains("list") && obj["list"].isArray())
            {
                for(short day=0; day<MyForecastWeather::NB_DAYS_FORECAST; ++day)
                {
                    for(short bloc=0; bloc<MyForecastWeather::NB_BLOCS_EACHDAY_FORECAST; ++bloc)
                    {
                        MyWeatherData * data = mWeaterForecast.getWeatherData(day, bloc);
                        int index = day*MyForecastWeather::NB_BLOCS_EACHDAY_FORECAST + bloc;

                        if (index < obj["list"].toArray().size())
                        {
                            QJsonObject blocData = obj["list"].toArray().at(index).toObject();

                            // TEMPERATURE
                            if (blocData.contains("main")
                             && blocData["main"].toObject().contains("temp"))
                            {
                                    QJsonValue temperature = blocData["main"].toObject()["temp"];
                                    data->setTemperature(temperature.toDouble());
                            }

                            // DATE TIME
                            if (blocData.contains("dt"))
                            {
                                int year, month, day, hour, minute, second;
                                QString dt_text = blocData["dt_txt"].toString();
                                sscanf(dt_text.toStdString().c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

                                data->setDateTime(QDateTime::fromTime_t(static_cast<unsigned int>(blocData["dt"].toInt())));
                            }

                            // ICON
                            if ( blocData.contains("weather")
                              && blocData["weather"].isArray()
                              && blocData["weather"].toArray().size() > 0 // TODO : why could it have more than 1 entry on this array ?
                              && blocData["weather"].toArray().at(0).toObject().contains("icon"))
                            {
                                            QString iconId = blocData["weather"].toArray().at(0).toObject()["icon"].toString();
                                            data->setIconId(iconId);
                            }
                        }
                    }
                }

                weatherForecastReady(&mWeaterForecast);
            }
        }
        else
        {
            qDebug()<<parseError.errorString();
        }
    }
}
/*
void MyRequestManager::iconReady(MyWeatherIcon * weatherIcon)
{
    emit iconReady(weatherIcon);
}
*/
/*
void MyRequestManager::parseIconReply()
{
    QNetworkReply * reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    if (reply != nullptr)
    {
        QByteArray byteArray = reply->readAll();

        QPixmap pixmap;
        bool b = pixmap.loadFromData(byteArray, "PNG");

        mCurrentWeather.setIcon(pixmap);

        if (mMapIconBeingDownloaded.end() != mMapIconBeingDownloaded.find(reply) )
        {
            QString id = mMapIconBeingDownloaded.value(reply);
            MyWeatherIcon * weatherIcon = new MyWeatherIcon(id, pixmap);
            iconReady(weatherIcon);
        }




    }
}
*/
