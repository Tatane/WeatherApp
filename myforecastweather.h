#ifndef MYFORECASTWEATHER_H
#define MYFORECASTWEATHER_H

#include <QObject>
#include <array>
#include "myweatherdata.h"

class MyForecastWeather
{
public:
    MyForecastWeather();
    ~MyForecastWeather();

    /***
     * day : 0 to 4... (TO SEE for the first blocs)
     * threeHoursBloc : bloc 0 : 0:00am to 2:59am
     *                  bloc 1 : 3:00am to 5:59am
     *                  bloc 7 : 9:00pm to 11:59pm
     */
    MyWeatherData * getWeatherData(short day, short threeHoursBloc);

    static const short NB_DAYS_FORECAST = 5;
    static const short NB_BLOCS_EACHDAY_FORECAST = 8;

private:
    //std::vector<std::vector<MyWeatherData*> > mData; // data for 5 days, 8 blocs (of 3 hours) for each day.
    std::array<std::array<MyWeatherData*, NB_BLOCS_EACHDAY_FORECAST>, NB_DAYS_FORECAST> mData;
};

#endif // MYFORECASTWEATHER_H
