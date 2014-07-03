#ifndef MESSAGEUPDATE_H
#define MESSAGEUPDATE_H

#include <QObject>
#include <GUI/ipelement.h>
#include <config/filecontrol.h>
#include <QDebug>

class messageUpdate : public QObject
{
    Q_OBJECT
public:
    explicit messageUpdate();
    messageUpdate(QList<ipElement> elementList, QObject *parent = 0);

    QList<ipElement> elementList;
    QList<qint64> logPosList;

signals:

public slots:
    int updateElements();

};

#endif // MESSAGEUPDATE_H
