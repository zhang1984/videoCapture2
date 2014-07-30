#ifndef CARDELEMENT_H
#define CARDELEMENT_H
#include <config/messagetype.h>
#include <GUI/channelelement.h>
/**
    \brief define the card element, include the channelElement and messageType of the card
*/
class cardElement
{
public:
    /**
    \brief initial the class
    */
    cardElement();
    /**
    \brief
    \param videoCard : the name of the videoCard
    */
    QString videoCard;
    /**
    \brief
    \param channelList : the list of channelElement under the video card
    */
    QList<channelElement> channelList;
    /**
    \brief
    \param vMessageList : the list of messageType under the video card
    */
    QList<messageType> vMessageList;
};

#endif // CARDELEMENT_H
