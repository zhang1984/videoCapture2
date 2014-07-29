#ifndef SERVERTYPE_H
#define SERVERTYPE_H

#include <QWidget>
#include <config/cardtype.h>
#include <config/streamtype.h>
#include <QList>
/**
\brief define the server type
*/
class serverType
{
public:
    /**
    \brief
    initial the serverType
    */
    serverType();
    /**
    \brief initial the serverType with parameters
    */
    serverType(QString projectName, QString ipAdd, QString serverName);
    /**
    \brief initial the serverType with parameters and the information about the streams and video cards
    */
    serverType(QString projectName, QString ipAdd, QString serverName, QList< streamtype> streamList, QList< cardtype> cardList);
    /**
    \brief
    \param projectName : the name of project
    */
    QString projectName;
    /**
    \brief
    \param ipAdd : the IP Address of the server
    */
    QString ipAdd;
    /**
    \brief
    \param serverName :the name of the server
    */
    QString serverName;
    /**
    \brief
    \param streamList : the list of the streamType in the server
    */
    QList< streamtype> streamList;
    /**
    \brief
    \param cardList : the list of the cardType in the server
    */
    QList< cardtype> cardList;
    /**
    \brief
    \param IOCapture : status of the server capture, 0 = stopped, 1 = started
    */
    int IOCapture;
    /**
    \brief get the video card name according to the number of channel
    */
    QString getVideoCard(int channel);
};

#endif // SERVERTYPE_H
