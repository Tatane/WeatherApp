#ifndef MYWEATHERICON_H
#define MYWEATHERICON_H

#include <QPixmap>
#include <QString>

class MyWeatherIcon
{
public:
    MyWeatherIcon(QString id, const QPixmap & pixmap);

    QString id() const;

    QPixmap & pixmap();

private:
    QString mId;
    QPixmap mPixmap;
};

#endif // MYWEATHERICON_H
