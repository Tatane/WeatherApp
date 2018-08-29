#include "formweatherdata.h"
#include "ui_formweatherdata.h"

#include <QDateTime>
#include "myweathericon.h"
#include "myweatherdata.h"

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

    QDateTime dateTime = weatherData()->getDateTime();
    ui->label_Day->setText(dateTime.toString("ddd dd"));
    ui->label_Month->setText(dateTime.toString("MMM"));
    ui->label_Hour->setText(dateTime.toString("HH") + "h");
}

void FormWeatherData::updateWeatherIcon(MyWeatherIcon * weatherIcon)
{
    ui->label_Icon->setPixmap(weatherIcon->pixmap());
}
