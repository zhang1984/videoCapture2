#include "messageupdate.h"

messageUpdate::messageUpdate(){}

messageUpdate::messageUpdate(QList<ipElement> List, QObject *parent) :
    QObject(parent)
{
    elementList = List;
    for(int i = 0; i < List.count(); i++)
    {
        logPosList.append(0);
    }
}

int messageUpdate::updateElements()
{
        for(int i = 0; i < elementList.count(); i++)
        {
            QString ipAdd = elementList.at(i).ipAdd;
            filecontrol _control;
            QList<messageType> messageList;
            qint64 pos = logPosList.at(i);
            _control.logPos = pos;
            messageList = _control.readLogFile(ipAdd, messageList);
            logPosList.replace(i, _control.logPos);
            for(int j = 0; j < messageList.count(); j++)
            {
                if(messageList.at(j).device.isEmpty())
                {
                    elementList[i].iMessageList.append(messageList.at(j));
                }
                else
                {
                    QList<cardtype> cardList = _control.readVideoChannelFile(ipAdd);
                    if(messageList.at(j).device.contains("card"))
                    {
                        int index = messageList.at(j).device.split(" ").at(1).toInt();
                        cardtype _ctype;
                        QString cardname = _ctype.getName(cardList, index);
                        int _find = 0;
                        int z = 0;
                        while(!_find && z < elementList.at(i).cardList.count())
                        {
                            if(elementList.at(i).cardList.at(z).videoCard == cardname)
                            {
                                _find = 1;
                                elementList[i].cardList[z].vMessageList.append(messageList.at(j));
                            }
                            z++;
                        }
                        if(!_find)
                        {
                            cardElement cardele;
                            cardele.videoCard = cardname;
                            cardele.vMessageList.append(messageList.at(j));

                            QList<int> _channelList = _ctype.getChannelList(cardList, cardname);
                            for(int  y = 0; y < _channelList.count(); y++)
                            {
                                channelElement channele;
                                channele.channelID = _channelList.at(y);
                                cardele.channelList.append(channele);
                            }
                            elementList[i].cardList.append(cardele);
                        }
                    }
                    else
                    {
                        if(messageList.at(j).device.contains("chan"))
                        {
                            qDebug()<<messageList.at(j).message;
                            qDebug()<<messageList.at(j).device;
                            int index = messageList.at(j).device.split(" ").at(1).toInt();
                            QString cardname = _control.getVideoCard(cardList, index);
                            int cardIndex = -1;
                            int channelIndex = -1;
                            int z = 0;
                            while(cardIndex == -1 && z < elementList.at(i).cardList.count())
                            {
                                if(cardname == elementList.at(i).cardList.at(z).videoCard)
                                {
                                    cardIndex = z;
                                    int y = 0;
                                    while(channelIndex == -1 && y < elementList.at(i).cardList.at(z).channelList.count())
                                    {
                                        if(index == elementList.at(i).cardList.at(z).channelList.at(y).channelID)
                                            channelIndex = y;
                                        y++;
                                    }
                                }
                                z++;
                            }
                            if(channelIndex != -1)
                            {
                                elementList[i].cardList[cardIndex].channelList[channelIndex].cMessageList.append(messageList.at(j));
                            }
                            else
                            {
                                if(cardIndex != -1)
                                {
                                    cardtype _ctype;
                                    QList<int> _channelList = _ctype.getChannelList(cardList, cardname);
                                    for(int x = 0; x < _channelList.count(); x++)
                                    {
                                        channelElement chanele;
                                        chanele.channelID = _channelList.at(x);
                                        if(_channelList.at(x) == messageList.at(j).device.split(" ").at(1).toInt())
                                        {
                                            chanele.cMessageList.append(messageList.at(j));
                                        }
                                        elementList[i].cardList[cardIndex].channelList.append(chanele);
                                    }
                                }
                                else
                                {
                                    cardElement cardele;
                                    cardele.videoCard = cardname;
                                    cardtype _ctype;
                                    QList<int> _channelList = _ctype.getChannelList(cardList, cardname);
                                    for(int x = 0; x < _channelList.count(); x++)
                                    {
                                        channelElement chanele;
                                        chanele.channelID = _channelList.at(x);
                                        if(_channelList.at(x) == messageList.at(j).device.split(" ").at(1).toInt())
                                        {
                                            chanele.cMessageList.append(messageList.at(j));
                                        }
                                        cardele.channelList.append(chanele);
                                    }
                                    elementList[i].cardList.append(cardele);
                                }
                            }
                        }
                    }
                }
            }
        }
        return 0;
}
