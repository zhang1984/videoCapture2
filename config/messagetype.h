#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QDebug>

/**
\brief define the message type from a line in dvs_sdi.log file
*/
class messageType
{
    //Q_OBJECT
public:
    /**
    \brief initial the messageType
    */
    explicit messageType();
    /**
    \brief initial the messageType with the parameter of the messageType
    */
    messageType(int datum, QString time, QString device, QString message, int type);
    /**
    \brief initial the messageType from the line text code in dvs_sdi.log
    */
    messageType(QString line);
    /**
    \brief
    \param datum : the day of the text
    */
    int datum;
    /**
    \brief
    \param time : the time code of the text
    */
    QString time;
    /**
    \brief
    \param message : the message text
    */
    QString message;
    /**
    \brief
    \param device : the device of the capture computer
    */
    QString device;
    /**
    \brief
    \param type : the type of the message. 1 = Good; 2 = Error; 3 = Warning; 4 = Sync Error
    */
    int type;
    /**
    \brief  hand out the message type from the message
    */
    int getMessageType(QString message);

//signals:

//public slots:

};

#endif // MESSAGETYPE_H
