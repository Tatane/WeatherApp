#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myforecastweather.h"
#include "formweatherdata.h"
#include "myweathericon.h"
#include <algorithm>

#include "myweathericonrequest.h"
#include "mysettings.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MySettings::getInstance();

    connect(MyRequestManager::getInstance(), SIGNAL(currentWeatherReady(MyWeatherData*)), this, SLOT(updateCurrentWeather(MyWeatherData*)));
    connect(MyRequestManager::getInstance(), SIGNAL(weatherForecastReady(MyForecastWeather*)), this, SLOT(updateWeatherForecast(MyForecastWeather*)));
    connect(MyRequestManager::getInstance(), SIGNAL(iconReady(MyWeatherIcon*)), this, SLOT(updateWeatherIcon(MyWeatherIcon*)));

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(refreshData()));

    // Create widgets FormWeatherData : one for the current weather, and NB_DAYS_FORECAST*NB_BLOCS_EACHDAY_FORECAST for the forecasts :
    for(int i=0; i<1 + MyForecastWeather::NB_DAYS_FORECAST*MyForecastWeather::NB_BLOCS_EACHDAY_FORECAST; ++i)
    {
        FormWeatherData * formWeatherData = new FormWeatherData;
        mVecFormWeatherData.push_back(formWeatherData);
        ui->verticalLayoutScrollArea->addWidget(formWeatherData);
    }

    refreshData();
}

MainWindow::~MainWindow()
{
    for(FormWeatherData * formWeatherData : mVecFormWeatherData)
    {
        delete formWeatherData;
        formWeatherData = nullptr;
    }

    for(std::pair<QString, MyWeatherIcon* > pair : mMapWeatherIcon)
    {
        MyWeatherIcon * weatherIcon = pair.second;
        delete weatherIcon;
        weatherIcon = nullptr;
    }

    delete ui;
}

void MainWindow::updateWeatherIcon(MyWeatherIcon * weatherIcon)
{
    if (mMapWeatherIcon.find(weatherIcon->id()) != mMapWeatherIcon.end())
    {
        // If a WeatherIcon with the same id has already been stored in the map, we can delete this useless one :
        delete weatherIcon;
        weatherIcon = nullptr;
    }
    else
    {
        // Store the WeatherIcon in the map. MainWindow is responsible to delete them later.
        mMapWeatherIcon[weatherIcon->id()] = weatherIcon;

        for(FormWeatherData* formWeatherData : mVecFormWeatherData)
        {
            if (formWeatherData->weatherData()->getIconId() == weatherIcon->id())
            {
                formWeatherData->updateWeatherIcon(weatherIcon);
            }
        }
    }
}

void MainWindow::updateCurrentWeather(MyWeatherData * weatherData)
{
    ui->labelCityName->setText(weatherData->getCityName());

    FormWeatherData * formWeatherData = mVecFormWeatherData.at(0); // the first Form of the vector is the Current Weather.
    formWeatherData->setWeatherData(weatherData);
    formWeatherData->refresh();

    if (mMapWeatherIcon.find(weatherData->getIconId()) != mMapWeatherIcon.end())
    {
        MyWeatherIcon * weatherIcon = mMapWeatherIcon.at(weatherData->getIconId());
        mVecFormWeatherData[0]->updateWeatherIcon(weatherIcon);
    }
    else
    {
        MyRequestManager::getInstance()->getIcon(weatherData->getIconId());
    }
}

void MainWindow::updateWeatherForecast(MyForecastWeather * myWeatherForecast)
{
    for(int day=0; day<MyForecastWeather::NB_DAYS_FORECAST; ++day)
    {
        for(int bloc=0; bloc<MyForecastWeather::NB_BLOCS_EACHDAY_FORECAST; ++bloc)
        {
            MyWeatherData * weatherData = myWeatherForecast->getWeatherData(day, bloc);
            FormWeatherData * formWeatherData = mVecFormWeatherData.at(1 + day*MyForecastWeather::NB_BLOCS_EACHDAY_FORECAST + bloc);

            formWeatherData->setWeatherData(weatherData);
            formWeatherData->refresh();

            if (mMapWeatherIcon.find(weatherData->getIconId()) != mMapWeatherIcon.end())
            {
                MyWeatherIcon * weatherIcon = mMapWeatherIcon.at(weatherData->getIconId());
                formWeatherData->updateWeatherIcon(weatherIcon);
            }
            else
            {
                MyRequestManager::getInstance()->getIcon(weatherData->getIconId()); // request the icon.
            }
        }
    }
}

void MainWindow::refreshData()
{
    int idMontreal = 6077246;
    MyRequestManager::getInstance()->getCurrentWeather(idMontreal);
    MyRequestManager::getInstance()->getForecastWeather(idMontreal);
}
