#include "errorwidget.h"

errorwidget::errorwidget(QWidget *parent) :
    QWidget(parent)
{
    CreateTreeWidget();
    message = new errormessages();
    connect(&upDateTimer, SIGNAL(timeout()), &_messUpdate, SLOT(updateElements()));
    connect(&upDateTimer, SIGNAL(timeout()), this, SLOT(updateTable()));
    _messUpdate.moveToThread(&_upDateThread);
    _upDateThread.start();
}

void errorwidget::CreateTreeWidget()
{
    errorWidget = new QTreeWidget();
    QStringList headList;
    headList<<"Name"<<"Good"<<"Error"<<"Waring"<<"SyncError";
    errorWidget->setHeaderLabels(headList);
    errorWidget->setExpandsOnDoubleClick(false);
    connect(errorWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(infoDialogShow(QTreeWidgetItem*,int)));
    //////////////////////TEST//////////////////////////
}

QTreeWidgetItem* errorwidget::setServerType(serverType _server)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, _server.ipAdd);
    if(_server.cardList.count() != 0)
    {
        for(int i = 0; i < _server.cardList.count(); i++)
        {
            QTreeWidgetItem* cardItem = new QTreeWidgetItem();
            cardItem->setText(0, _server.cardList.at(i).name);

            for(int j = 0; j < _server.cardList.at(i).channelList.count(); j++)
            {
                QTreeWidgetItem* channelItem = new QTreeWidgetItem();
                channelItem->setText(0, QString("Channel %1").arg(_server.cardList.at(i).channelList.at(j)));
                cardItem->addChild(channelItem);
            }
            item->addChild(cardItem);
        }
    }
    else
    {
        QTreeWidgetItem* cardItem = new QTreeWidgetItem();
        cardItem->setText(0, "Video Card 0");
        item->addChild(cardItem);
    }

    for(int i = 0; i < _server.streamList.count(); i++)
    {
        QTreeWidgetItem* streamItem = new QTreeWidgetItem();
        streamItem->setText(0, QString("Stream %1").arg(_server.streamList.at(i).streamID));
        int channelIndex = _server.streamList.at(i).channel;
        int _find = 0;
        for(int k = 0; k < item->childCount() && !_find; k++)
        {
            for(int l = 0; l < item->child(k)->childCount() && !_find; l++)
            {
                if(item->child(k)->child(l)->text(0).remove("Channel ").toInt() == channelIndex)
                {
                    _find = 1;
                    item->child(k)->child(l)->addChild(streamItem);
                }
            }
        }

        if(!_find)
        {
            QTreeWidgetItem* channelItem = new QTreeWidgetItem();
            channelItem->setText(0, QString("Channel %1").arg(channelIndex));
            channelItem->addChild(streamItem);
            item->child(0)->addChild(channelItem);
        }
    }
    return item;
}

void errorwidget::addTreeItem(serverType _server)
{
    int _inTree = 0;
    int i = 0;
    while(i < errorWidget->topLevelItemCount() && !_inTree)
    {
        if(errorWidget->topLevelItem(i)->text(0) == _server.ipAdd)
        {
            _inTree = 1;
        }
        i++;
    }
    if(!_inTree)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item = this->setServerType(_server);
        errorWidget->addTopLevelItem(item);
        ipElement element;
        element.ipAdd = _server.ipAdd;
        elementList.append(element);
        logPosList.append(0);
    }
    if(upDateTimer.isActive())
    {
        upDateTimer.stop();
        if(logPosList.count() > _messUpdate.logPosList.count())
            _messUpdate.logPosList.append(0);
        _messUpdate.elementList = elementList;
        upDateTimer.start(1000);
    }
    else
    {
        if(logPosList.count() > _messUpdate.logPosList.count())
            _messUpdate.logPosList.append(0);
        _messUpdate.elementList = elementList;
        upDateTimer.start(1000);

    }
}



void errorwidget::addTreeItem(QString ipAdd, QString cardName, int channel, int stream)
{
    int serverIndex = -1;
    int cardIndex = -1;
    int channelIndex = -1;
    int streamIndex = -1;
    for(int i = 0; i < errorWidget->topLevelItemCount() && serverIndex == -1; i++)
    {
        if(errorWidget->topLevelItem(i)->text(0) == ipAdd)
        {
            serverIndex = i;
            for(int j = 0; j < errorWidget->topLevelItem(i)->childCount() && cardIndex == -1; j++)
            {
                if(errorWidget->topLevelItem(i)->child(j)->text(0) == cardName)
                {
                    cardIndex = j;
                    for(int k = 0; k < errorWidget->topLevelItem(i)->child(j)->childCount() && channelIndex == -1; k++)
                    {
                        QString _temp = errorWidget->topLevelItem(i)->child(j)->child(k)->text(0);
                        _temp = _temp.remove("Channel ");
                        if(_temp.toInt() == channel)
                        {
                            channelIndex = k;
                            for(int l = 0; l < errorWidget->topLevelItem(i)->child(j)->child(k)->childCount() && streamIndex == -1; l++)
                            {
                                QString _temp = errorWidget->topLevelItem(i)->child(j)->child(k)->child(l)->text(0);
                                _temp = _temp.remove("Stream ");
                                if(_temp.toInt() == stream)
                                {
                                    streamIndex = l;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(streamIndex == -1)
    {
        QTreeWidgetItem* streamItem = new QTreeWidgetItem();
        streamItem->setText(0, QString("Stream %1").arg(stream));
        if(channelIndex != -1)
        {
            errorWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->addChild(streamItem);
        }
        else
        {
            QTreeWidgetItem* channelItem = new QTreeWidgetItem();
            channelItem->setText(0, QString("Channel %1").arg(channel));
            channelItem->addChild(streamItem);
            if(cardIndex != -1)
            {
                errorWidget->topLevelItem(serverIndex)->child(cardIndex)->addChild(channelItem);
            }
            else
            {
                QTreeWidgetItem* cardItem = new QTreeWidgetItem();
                cardItem->setText(0, "Video Card 0");
                cardItem->addChild(channelItem);
                errorWidget->topLevelItem(serverIndex)->addChild(cardItem);
            }
        }
    }
    /*if(upDateTimer.isActive())
    {
        upDateTimer.stop();
        if(logPosList.count() > _messUpdate.logPosList.count())
            _messUpdate.logPosList.append(0);
        _messUpdate.elementList = elementList;
        upDateTimer.start(1000);
    }
    else
    {
        if(logPosList.count() > _messUpdate.logPosList.count())
            _messUpdate.logPosList.append(0);
        _messUpdate.elementList = elementList;
        upDateTimer.start(1000);
    }*/
    //this->updateTable();
}

int errorwidget::removeServer(QString ipAdd)
{
    int _find = 0;
    int i = 0;
    while(!_find && i < errorWidget->topLevelItemCount())
    {
        if(errorWidget->topLevelItem(i)->text(0) == ipAdd)
        {
            errorWidget->takeTopLevelItem(i);
            _find = 1;
        }
        i++;
    }
    _find = 0;
    i = 0;
    while(!_find && i < elementList.count())
    {
        if(elementList.at(i).ipAdd == ipAdd)
        {
            _find = 1;
            elementList.takeAt(i);
            logPosList.takeAt(i);
        }
        i++;
    }
    return 0;
}

void errorwidget::updateElements()
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
                    if(_find)
                    {
                        cardElement cardele;
                        cardele.videoCard = cardname;
                        cardele.vMessageList.append(messageList.at(j));
                        QList<int> _channelList = _ctype.getChannelList(cardList, cardname);
                        for(int y = 0; y < _channelList.count(); y++)
                        {
                            channelElement chanele;
                            chanele.channelID = _channelList.at(y);
                            cardele.channelList.append(chanele);
                        }
                    }
                }
                else
                {
                    if(messageList.at(j).device.contains("chan"))
                    {
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
                                    {
                                        channelIndex = y;
                                    }
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
                                int x = 0;
                                for(x = 0; x < _channelList.count(); x++)
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
                                int x = 0;
                                for(x = 0; x < _channelList.count(); x++)
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
}

QList<int> errorwidget::getMessageListStatic(QList<messageType> list)
{
    int good = 0;
    int error = 0;
    int warning = 0;
    int sync = 0;
    for(int i = 0; i < list.count(); i++)
    {
        if(list.at(i).type == 1)
            good++;
        if(list.at(i).type == 2)
            error++;
        if(list.at(i).type == 3)
            warning++;
        if(list.at(i).type == 4)
            sync++;
    }
    QList<int> _r;
    _r.append(good);
    _r.append(error);
    _r.append(warning);
    _r.append(sync);
    return _r;
}

/////////////////////////////////SLOTS////////////////////////////////////////////////
void errorwidget::infoDialogShow(QTreeWidgetItem* item, int column)
{
    if(column != 0)
    {
        int chanNum = -1;
        QString videoCard;
        QString ipAdd;
        if(!item->text(column).isNull() && !item->text(column).isEmpty())
        {
            QList<messageType> messageList;
            if(item->text(0).contains("Channel"))
            {
                chanNum = item->text(0).remove("Channel ").toInt();
                videoCard = item->parent()->text(0);
                ipAdd = item->parent()->parent()->text(0);

                int _find = 0;
                int i = 0;
                while(!_find && i < elementList.count())
                {
                    if(elementList.at(i).ipAdd == ipAdd)
                    {
                        int j = 0;
                        while(!_find && j < elementList.at(i).cardList.count())
                        {
                            if(elementList.at(i).cardList.at(j).videoCard == videoCard)
                            {
                                int k = 0;
                                while(!_find && k < elementList.at(i).cardList.at(j).channelList.count())
                                {
                                    if(elementList.at(i).cardList.at(j).channelList.at(k).channelID == chanNum)
                                    {
                                        _find = 1;
                                        messageList = elementList.at(i).cardList.at(j).channelList.at(k).cMessageList;
                                    }
                                    k++;
                                }
                            }
                            j++;
                        }
                    }
                    i++;
                }
            }
            else
            {
                if(item->parent() != 0 && !item->text(0).contains("Channel"))
                {
                    videoCard = item->text(0);
                    ipAdd = item->parent()->text(0);

                    int _find = 0;
                    int i = 0;
                    while(!_find && i < elementList.count())
                    {
                        if(elementList.at(i).ipAdd == ipAdd)
                        {
                            int j = 0;
                            while(!_find && j < elementList.at(i).cardList.count())
                            {
                                if(elementList.at(i).cardList.at(j).videoCard == videoCard)
                                {
                                    _find = 1;
                                    messageList = elementList.at(i).cardList.at(j).vMessageList;
                                }
                                j++;
                            }
                        }
                        i++;
                    }
                }
                else
                {
                    ipAdd = item->text(0);
                    int _find = 0;
                    int i = 0;
                    while(!_find && i < elementList.count())
                    {
                        if(elementList.at(i).ipAdd == ipAdd)
                        {
                            _find = 1;
                            messageList = elementList.at(i).iMessageList;
                        }
                        i++;
                    }
                }
            }

            message->setTable(messageList, column);
            message->dialog->open();
        }
    }

}



void errorwidget::updateTable()
{
    elementList = _messUpdate.elementList;
    for(int i = 0; i < errorWidget->topLevelItemCount(); i++)
    {
            QString ipAdd = errorWidget->topLevelItem(i)->text(0);
            int _server_find = 0;
            int j = 0;
            while(!_server_find && j < elementList.count())
            {
                if(ipAdd == elementList.at(j).ipAdd)
                {
                    QList<int> staticList = this->getMessageListStatic(elementList.at(j).iMessageList);
                    QString text1 = QString("%1").arg(staticList.at(0));
                    QString text2 = QString("%1").arg(staticList.at(1));
                    QString text3 = QString("%1").arg(staticList.at(2));
                    QString text4 = QString("%1").arg(staticList.at(3));
                    errorWidget->topLevelItem(i)->setText(1, text1);
                    errorWidget->topLevelItem(i)->setText(2, text2);
                    errorWidget->topLevelItem(i)->setText(3, text3);
                    errorWidget->topLevelItem(i)->setText(4, text4);
                    _server_find = 1;
                    QList<cardElement> cardList = elementList.at(j).cardList;
                    for(int k = 0; k < errorWidget->topLevelItem(i)->childCount(); k++)
                    {
                        QString cardname = errorWidget->topLevelItem(i)->child(k)->text(0);
                        int _card_find = 0;
                        int l = 0;
                        while(!_card_find && l < cardList.count())
                        {
                            if(cardname == cardList.at(l).videoCard)
                            {
                                staticList = this->getMessageListStatic(cardList.at(l).vMessageList);
                                QString text1 = QString("%1").arg(staticList.at(0));
                                QString text2 = QString("%1").arg(staticList.at(1));
                                QString text3 = QString("%1").arg(staticList.at(2));
                                QString text4 = QString("%1").arg(staticList.at(3));
                                errorWidget->topLevelItem(i)->child(k)->setText(1, text1);
                                errorWidget->topLevelItem(i)->child(k)->setText(2, text2);
                                errorWidget->topLevelItem(i)->child(k)->setText(3, text3);
                                errorWidget->topLevelItem(i)->child(k)->setText(4, text4);
                                _card_find = 1;
                                QList<channelElement> channelList = elementList.at(j).cardList.at(l).channelList;
                                for(int m = 0; m < errorWidget->topLevelItem(i)->child(k)->childCount(); m++)
                                {
                                    int channelIndex = errorWidget->topLevelItem(i)->child(k)->child(m)->text(0).remove("Channel ").toInt();
                                    int _channel_find = 0;
                                    int n = 0;
                                    while(!_channel_find && n < channelList.count())
                                    {
                                        if(channelIndex == channelList.at(n).channelID)
                                        {
                                            staticList = this->getMessageListStatic(channelList.at(n).cMessageList);
                                            QString text1 = QString("%1").arg(staticList.at(0));
                                            QString text2 = QString("%1").arg(staticList.at(1));
                                            QString text3 = QString("%1").arg(staticList.at(2));
                                            QString text4 = QString("%1").arg(staticList.at(3));
                                            errorWidget->topLevelItem(i)->child(k)->child(m)->setText(1, text1);
                                            errorWidget->topLevelItem(i)->child(k)->child(m)->setText(2, text2);
                                            errorWidget->topLevelItem(i)->child(k)->child(m)->setText(3, text3);
                                            errorWidget->topLevelItem(i)->child(k)->child(m)->setText(4, text4);
                                            _channel_find = 1;
                                        }
                                        n++;
                                    }
                                }
                            }
                            l++;
                        }
                    }
                }
                j++;
            }
    }
}
