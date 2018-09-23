#include "myweathericon.h"

MyWeatherIcon::MyWeatherIcon(QString id, const QPixmap & pixmap)
    : mId(id)
    , mPixmap(pixmap)
{

}

QString MyWeatherIcon::id() const
{
    return mId;
}

QPixmap & MyWeatherIcon::pixmap()
{
    return mPixmap;
}
