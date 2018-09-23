#include "myweathericonrequest.h"

#include "myweathericon.h"

MyWeatherIconRequest::MyWeatherIconRequest(QString iconId, QNetworkReply *reply)
    : mIconId(iconId)
    , mReply(reply)
{
    connect(mReply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void MyWeatherIconRequest::replyFinished()
{
    // Parse reply, and extract pixmap.

    QNetworkReply * reply = dynamic_cast<QNetworkReply*>(QObject::sender());
    if (reply != nullptr)
    {
        QByteArray byteArray = reply->readAll();

        QPixmap pixmap;
        bool b = pixmap.loadFromData(byteArray, "PNG");

        if (true == b)
        {
            MyWeatherIcon * weatherIcon = new MyWeatherIcon(mIconId, pixmap);
            emit iconReady(weatherIcon);
        }
    }
}
