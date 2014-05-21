#ifndef CARDELEMENT_H
#define CARDELEMENT_H
#include <config/messagetype.h>
#include <GUI/channelelement.h>

class cardElement
{
public:
    cardElement();
    QString videoCard;
    QList<channelElement> channelList;
    QList<messageType> vMessageList;
};

#endif // CARDELEMENT_H
