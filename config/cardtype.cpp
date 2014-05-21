#include "cardtype.h"

cardtype::cardtype()
{}

cardtype::cardtype(int index, QString Name, QList< int> channelList)
{
    this->index = index;
    this->name = Name;
    for(int i = 0; i < channelList.count(); i++)
    {
        this->channelList.append(channelList.at(i));
    }
}

int cardtype::compare(cardtype _card)
{
    if(index != _card.index)
    {
        return 0;
    }
    if(name != _card.name)
    {
        return 0;
    }
    if(channelList != _card.channelList)
    {
        return 0;
    }
    return 1;
}

QString cardtype::getName(QList<cardtype> cardList, int index)
{
    int _find = 0;
    int i = 0;
    QString name;
    while(!_find && i < cardList.count())
    {
        if(cardList.at(i).index == index)
        {
            _find = 1;
            name = cardList.at(i).name;
        }
        i++;
    }
    return name;
}

QList<int> cardtype::getChannelList(QList<cardtype> cardList, QString name)
{
    int _find = 0;
    int i = 0;
    QList<int> list;
    while(!_find && i < cardList.count())
    {
        if(cardList.at(i).name == name)
        {
            list = cardList.at(i).channelList;
            _find = 1;
        }
        i++;
    }
    return list;
}
