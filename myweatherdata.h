#ifndef MYWEATHERDATA_H
#define MYWEATHERDATA_H

#include <QObject>
#include <QPixmap>
#include <QDateTime>

class MyWeatherData
{
public:
    MyWeatherData();
    double getTemperature() const;
    void setTemperature(double t);
    QString getIconId() const;
    void setIconId(QString s);
    QString getCityName() const;
    void setCityName(QString cityName);
    QDateTime getDateTime() const;
    void setDateTime(QDateTime dateTime);
    QString getDescription() const;
    void setDescription(const QString &value);

private:
    QDateTime mDateTime;
    double mTemperature;
    QString mIconId;
    QString mCityName;
    QString description;
};

#endif // MYWEATHERDATA_H
