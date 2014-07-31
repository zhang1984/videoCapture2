#ifndef IPELEMENT_H
#define IPELEMENT_H

#include <config/messagetype.h>
#include <GUI/cardelement.h>
/**
\brief define the ip elements (server elements)
*/
class ipElement
{
public:
    /**
    \brief initial
    */
    ipElement();
    /**
    \brief
    \param ipAdd : the ip address of the server
    */
    QString ipAdd;
    /**
    \brief
    \param cardList : the list of the card under the server
    */
    QList< cardElement> cardList;
    /**
    \brief
    \param iMessageList : the messageList of the server
    */
    QList<messageType> iMessageList;
};

#endif // IPELEMENT_H
