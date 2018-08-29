#ifndef MYWEATHERICONREQUEST_H
#define MYWEATHERICONREQUEST_H

#include <QString>
#include <QNetworkReply>
class MyWeatherIcon;

class MyWeatherIconRequest : public QObject
{
    Q_OBJECT

public:
    MyWeatherIconRequest(QString mIconId, QNetworkReply * mReply);

private:
    QString mIconId;
    QNetworkReply * mReply;

private slots:
    void replyFinished();

signals:
    void iconReady(MyWeatherIcon*);
};

#endif // MYWEATHERICONREQUEST_H
