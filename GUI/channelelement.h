#ifndef CHANNELELEMENT_H
#define CHANNELELEMENT_H

#include <config/messagetype.h>

/**
\brief define a channelElement
*/
class channelElement
{
public:
    /**
    \brief initial channelElement
    */
    channelElement();
    /**
    \brief
    \param channelID : the channel id
    */
    int channelID;
    /**
    \brief
    \param cMessageList : the list of messageTypes in the channel
    */
    QList<messageType> cMessageList;
};

#endif // CHANNELELEMENT_H
