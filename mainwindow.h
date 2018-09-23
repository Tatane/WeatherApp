#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <myrequestmanager.h>
#include <formweatherdata.h>
#include <QQueue>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::vector<FormWeatherData*> mVecFormWeatherData; // vector of widgets, each displaying one of the periods of weather.
    std::map<QString, MyWeatherIcon*> mMapWeatherIcon; // Store icons downloaded from the server.

private slots:
    void updateCurrentWeather(MyWeatherData*);
    void updateWeatherIcon(MyWeatherIcon*);
    void updateWeatherForecast(MyForecastWeather*);
    void refreshData();
};

#endif // MAINWINDOW_H
