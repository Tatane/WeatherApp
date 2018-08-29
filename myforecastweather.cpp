#include "myforecastweather.h"

MyForecastWeather::MyForecastWeather()
{
    for(int day=0; day<NB_DAYS_FORECAST; ++day)
    {
        for(int bloc=0; bloc<NB_BLOCS_EACHDAY_FORECAST; ++bloc)
        {
            mData[day][bloc] = new MyWeatherData;
        }

    }

}

MyWeatherData *MyForecastWeather::getWeatherData(short day, short threeHoursBloc)
{
    return mData[day][threeHoursBloc];
}
