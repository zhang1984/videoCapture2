#include "servertype.h"

serverType::serverType(){}
serverType::serverType(QString projectName, QString ipAdd, QString serverName)
{
    this->projectName = projectName;
    this->ipAdd = ipAdd;
    this->serverName = serverName;
}
serverType::serverType(QString projectName, QString ipAdd, QString serverName, QList< streamtype> streamList, QList< cardtype> cardList)
{
    this->projectName = projectName;
    this->ipAdd = ipAdd;
    this->serverName = serverName;
    for(int i = 0; i < streamList.count(); i++)
    {
        this->streamList.append(streamList.at(i));
    }
    for(int i = 0; i < cardList.count(); i++)
    {
        this->cardList.append(cardList.at(i));
    }
}

QString serverType::getVideoCard(int channel)
{
    int videoCard = -1;
    QString videoCardName;
    int i = 0;
    while(videoCard == -1 && i < cardList.count())
    {
        int j = 0;
        while(videoCard == -1 && j < cardList.at(i).channelList.count())
        {
            if(cardList.at(i).channelList.at(j) == channel)
            {
                videoCardName = cardList.at(i).name;
                videoCard = 0;
            }
            j++;
        }
        i++;
    }
    return videoCardName;
}
