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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::vector<FormWeatherData*> mVecFormWeatherData;

    //void downloadIcon(QString iconId);

    //QQueue<QString> mQueueIconIdToDownload;


private slots:
    void updateCurrentWeather(MyWeatherData*);
    void updateWeatherIcon(MyWeatherIcon*);
    void updateWeatherForecast(MyForecastWeather*);
    void refreshData();

private:
    //std::map<QString, QPixmap> mMapIcons;
    //QVector<MyWeatherIcon*> mVecIcons;
    std::map<QString, MyWeatherIcon*> mMapWeatherIcon;
};

#endif // MAINWINDOW_H
