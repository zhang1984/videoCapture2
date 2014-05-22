#ifndef TIMEUPDATE_H
#define TIMEUPDATE_H

#include <QObject>
#include <QTime>

class timeUpdate : public QObject
{
    Q_OBJECT
public:
    explicit timeUpdate(QObject *parent = 0);
//Todo: Add the function for currentTime, duration, split...
    QTime currentTime;
    QTime duration;
    QTime lastSplit;
    QTime nextSplit;

    QString currentTime_s;
    QString duration_s;
    QString lastSplit_s;
    QString nextSplit_s;
signals:

public slots:

};

#endif // TIMEUPDATE_H
