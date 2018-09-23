#include "formweatherdata.h"
#include "ui_formweatherdata.h"

#include <QDateTime>
#include "myweathericon.h"
#include "myweatherdata.h"
#include "mysettings.h"
#include <QPainter>

FormWeatherData::FormWeatherData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWeatherData)
{
    ui->setupUi(this);
}

FormWeatherData::~FormWeatherData()
{
    delete ui;
}



const MyWeatherData *FormWeatherData::weatherData() const
{
    return mWeatherData;
}

void FormWeatherData::setWeatherData(const MyWeatherData *weatherData)
{
    mWeatherData = weatherData;
}

void FormWeatherData::refresh()
{
    ui->label_Temperature->setText(QString::number(weatherData()->getTemperature(), 'f', 1) + " °C");

    QLocale locale = MySettings::getInstance()->getLocale();

    QDateTime dateTime = weatherData()->getDateTime();
    if (QDateTime::currentDateTime().daysTo(dateTime) < 3)
    {
        ui->label_Day->setText(locale.toString(dateTime, "dddd"));
    }
    else
    {
        ui->label_Day->setText(locale.toString(dateTime, "ddd dd"));
    }
    ui->label_Month->setText(locale.toString(dateTime, "MMM"));
    ui->label_Hour->setText(dateTime.toString("HH") + "h");
    ui->label_Icon->setText(weatherData()->getDescription());
    ui->label_Icon->setToolTip(weatherData()->getDescription());
}

void FormWeatherData::updateWeatherIcon(MyWeatherIcon * weatherIcon)
{
    QPixmap pixmap = weatherIcon->pixmap();
    pixmap = pixmap.copy(0, 8, 50, 32); // Crop icon, as a lot of pixels are not used.
    ui->label_Icon->setPixmap(pixmap);
}
