#ifndef CHANNELELEMENT_H
#define CHANNELELEMENT_H

#include <config/messagetype.h>
class channelElement
{
public:
    channelElement();
    int channelID;
    QList<messageType> cMessageList;
};

#endif // CHANNELELEMENT_H
