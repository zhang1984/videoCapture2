#ifndef IPELEMENT_H
#define IPELEMENT_H

#include <config/messagetype.h>
#include <GUI/cardelement.h>
class ipElement
{
public:
    ipElement();
    QString ipAdd;
    QList< cardElement> cardList;
    QList<messageType> iMessageList;
};

#endif // IPELEMENT_H
