#ifndef MESSAGEUPDATE_H
#define MESSAGEUPDATE_H

#include <QObject>
#include <GUI/ipelement.h>
#include <config/filecontrol.h>
#include <QDebug>

/**
\brief define a object for Multithread message update
*/
class messageUpdate : public QObject
{
    Q_OBJECT
public:
    /**
    \brief initial messageUpdate
    */
    explicit messageUpdate();
    /**
    \brief initial messageUpdate with elementList
    */
    messageUpdate(QList<ipElement> elementList, QObject *parent = 0);
    /**
    \brief
    \param elementList : the list of ipElement
    */
    QList<ipElement> elementList;
    /**
    \brief
    \param logPosList : the list of the read position of dvs_sdi.log file
    */
    QList<qint64> logPosList;

signals:

public slots:
    /**
    \brief slot, to update the messageType list of ipElement in the elementList
    */
    int updateElements();

};

#endif // MESSAGEUPDATE_H
