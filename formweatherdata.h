#ifndef FORMWEATHERDATA_H
#define FORMWEATHERDATA_H

#include <QWidget>

class MyWeatherIcon;
class MyWeatherData;

namespace Ui {
class FormWeatherData;
}

class FormWeatherData : public QWidget
{
    Q_OBJECT

public:
    explicit FormWeatherData(QWidget *parent = nullptr);
    ~FormWeatherData();

    const MyWeatherData *weatherData() const;
    void setWeatherData(const MyWeatherData *weatherData);
    void refresh();

private:
    Ui::FormWeatherData *ui;

    const MyWeatherData * mWeatherData;

    // ? Could we store the weather icons in this class ? instead of the mainwindow, as static.
    // Except if w esomehow need icons somewhere else than this form, somewhere else in the app.

public slots:
    void updateWeatherIcon(MyWeatherIcon*);
};

#endif // FORMWEATHERDATA_H
