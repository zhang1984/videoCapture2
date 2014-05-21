#include "treewidget.h"

treewidget::treewidget()
{
    createtWidget();
    createButtonWidget();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(tWidget, 0, 0, 4, 1);
    layout->addWidget(buttonWidget, 5, 0, 1, 1);
    QWidget* widget = new QWidget();
    widget->setLayout(layout);

    projectWidget = new QDockWidget();
    projectWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    projectWidget->setWidget(widget);

}

void treewidget::createButtonWidget()
{
    startButton = new QPushButton();
    startButton->setToolTip("Start all capture");
    startButton->setIcon(QIcon(":resource/start_icon.png"));
    stopButton = new QPushButton();
    stopButton->setToolTip("Stop all capture");
    stopButton->setIcon(QIcon(":resource/stop_icon.png"));
    addButton = new QPushButton();
    addButton->setToolTip("add...");
    addButton->setIcon(QIcon(":resource/add_icon.png"));
    addButton->setEnabled(false);
    minusButton = new QPushButton();
    minusButton->setToolTip("Remove...");
    minusButton->setIcon(QIcon(":resource/minus_icon.png"));
    minusButton->setEnabled(false);
    refreshButton = new QPushButton();
    refreshButton->setToolTip("Reload all");
    refreshButton->setIcon(QIcon(":resource/refresh_icon.png"));
    refreshButton->setEnabled(false);
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(startButton, 0, 0);
    layout->addWidget(stopButton, 0, 1);
    layout->addWidget(addButton, 1, 0);
    layout->addWidget(minusButton, 1, 1);
    layout->addWidget(refreshButton, 1, 2);
    buttonWidget = new QWidget();
    buttonWidget->setLayout(layout);
}

void treewidget::createtWidget()
{
    tWidget = new QTreeWidget();
    tWidget->setColumnCount(3);
    tWidget->header()->setVisible(false);
    tWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    tWidget->setExpandsOnDoubleClick(false);
}

QTreeWidgetItem* treewidget::createTreeItem(serverType server)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, server.ipAdd);
    item->setText(1, server.projectName);

    if(server.cardList.count() != 0)
    {
        for(int i = 0; i < server.cardList.count(); i++)
        {
            QTreeWidgetItem* cardItem = new QTreeWidgetItem();
            cardItem->setText(1, "Video Card");
            cardItem->setText(2, server.cardList.at(i).name);
            for(int j = 0; j < server.cardList.at(i).channelList.count(); j++)
            {
                QTreeWidgetItem* channelItem = new QTreeWidgetItem();
                channelItem->setText(1, "Channel");
                channelItem->setText(2, QString("%1").arg(server.cardList.at(i).channelList.at(j)));
                cardItem->addChild(channelItem);
            }
            item->addChild(cardItem);
        }
    }
    else
    {
        QTreeWidgetItem* cardItem = new QTreeWidgetItem();
        cardItem->setText(1, "Video Card");
        cardItem->setText(2, "0");
        item->addChild(cardItem);
    }

    for(int i = 0; i < server.streamList.count(); i++)
    {
        QTreeWidgetItem* streamItem = new QTreeWidgetItem();
        streamItem->setText(1, "Stream");
        streamItem->setText(2, QString("%1").arg(server.streamList.at(i).streamID));
        for(int j = 0; j < server.streamList.at(i).formatList.count(); j++)
        {
            QTreeWidgetItem* formatItem = new QTreeWidgetItem();
            formatItem->setText(1, "Format");
            formatItem->setText(2, server.streamList.at(i).formatList.at(j).codec);
            streamItem->addChild(formatItem);
        }
        int channelIndex = server.streamList.at(i).channel;
        int _find = 0;
        for(int k = 0; k < item->childCount() && !_find; k++)
        {
            for(int l = 0; l < item->child(k)->childCount() && !_find; l++)
            {
                if(item->child(k)->child(l)->text(2).toInt() == channelIndex)
                {
                    _find = 1;
                    item->child(k)->child(l)->addChild(streamItem);
                }
            }
        }

        if(!_find)
        {
            qDebug()<<"!_find "<<"channelIndex"<<channelIndex;
            QTreeWidgetItem* channelItem = new QTreeWidgetItem();
            channelItem->setText(1, "Channel");
            channelItem->setText(2, QString("%1").arg(channelIndex));
            channelItem->addChild(streamItem);
            item->child(0)->addChild(channelItem);
        }
    }
    return item;
}

void treewidget::addServerItem(serverType server)
{
    int _inTree = 0;
    int i = 0;
    while(i < tWidget->topLevelItemCount() && !_inTree)
    {
        if(tWidget->topLevelItem(i)->text(0) == server.ipAdd)
        {
            _inTree = 1;
        }
        i++;
    }

    if(!_inTree)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item = this->createTreeItem(server);
        QPushButton* ioButton = new QPushButton();
        if(server.IOCapture)
        {
            ioButton->setIcon(QIcon(":resource/stop_icon.png"));
            ioButton->setText("Start");
        }
        else
        {
            ioButton->setIcon(QIcon(":resource/start_icon.png"));
            ioButton->setText("Stop");
        }
        this->tWidget->addTopLevelItem(item);
        this->tWidget->setItemWidget(item, 2, ioButton);
    }
}

void treewidget::addFormatItem(serverType _server, QString cardName, streamtype _stream, formatType _format, int streamExists = 0)
{
    QString ipAdd = _server.ipAdd;
    int channelID = _stream.channel;
    QString cardname = cardName;
    int streamID = _stream.streamID;
    QList<cardtype> cardList = _server.cardList;
    int _find = 0;
    for(int i = 0; i < cardList.count() && !_find; i++)
    {
        for(int j = 0; j < cardList.at(i).channelList.count() && !_find; j++)
        {
            if(cardList.at(i).channelList.at(j) == channelID)
            {
                _find = 1;
                cardname = cardList.at(i).name;
            }
        }
    }
    QTreeWidgetItem* formatItem = new QTreeWidgetItem();
    formatItem->setText(1, "Format");
    formatItem->setText(2, _format.codec);

    int serverIndex = -1;
    int cardIndex = -1;
    int channelIndex = -1;
    int streamIndex = -1;
    for(int i = 0; i < tWidget->topLevelItemCount() && serverIndex == -1; i++)
    {
        if(tWidget->topLevelItem(i)->text(0) == ipAdd)
        {
            serverIndex = i;
            for(int j = 0; j < tWidget->topLevelItem(i)->childCount() && cardIndex == -1; j++)
            {
                if(tWidget->topLevelItem(i)->child(j)->text(2) == cardname)
                {
                    cardIndex = j;
                    for(int k = 0; k < tWidget->topLevelItem(i)->child(j)->childCount() && channelIndex == -1; k++)
                    {
                        if(tWidget->topLevelItem(i)->child(j)->child(k)->text(2).toInt() == channelID)
                        {
                            channelIndex = k;
                            for(int l = 0; l < tWidget->topLevelItem(i)->child(j)->child(k)->childCount() && streamIndex == -1; l++)
                            {
                                if(tWidget->topLevelItem(i)->child(j)->child(k)->child(l)->text(2).toInt() == streamID)
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

    if(streamIndex != -1)
    {
        tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->child(streamIndex)->addChild(formatItem);
    }
    else
    {
        QTreeWidgetItem* streamItem = new QTreeWidgetItem();
        streamItem->setText(1, "Stream");
        streamItem->setText(2, QString("%1").arg(_stream.streamID));
        streamItem->addChild(formatItem);
        if(channelIndex != -1)
        {
            tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->addChild(streamItem);
        }
        else
        {
            QTreeWidgetItem* channelItem = new QTreeWidgetItem();
            channelItem->setText(1, "Channel");
            channelItem->setText(2, QString("%1").arg(_stream.channel));
            channelItem->addChild(streamItem);
            if(cardIndex != -1)
            {
                tWidget->topLevelItem(serverIndex)->child(cardIndex)->addChild(channelItem);
            }
            else
            {
                QTreeWidgetItem* cardItem = new QTreeWidgetItem();
                cardItem->setText(1, "Video Card");
                cardItem->setText(2, cardname);
                cardItem->addChild(channelItem);
                tWidget->topLevelItem(serverIndex)->addChild(cardItem);
            }
        }
    }
}

int treewidget::removeFormatItem(QString server, QString videocard, int channel, int stream, QString format)
{
    int _find = 0;
    int i = 0;
    int serverIndex = -1;
    int cardIndex = -1;
    int channelIndex = -1;
    int streamIndex = -1;
    int formatIndex = -1;
    while(i < tWidget->topLevelItemCount() && !_find)
    {
        if(tWidget->topLevelItem(i)->text(0) == server)
        {
            serverIndex = i;
            int j = 0;
            while(j < tWidget->topLevelItem(i)->childCount() && !_find)
            {
                if(tWidget->topLevelItem(i)->child(j)->text(2) == videocard)
                {
                    cardIndex = j;
                    int k = 0;
                    while(k < tWidget->topLevelItem(i)->child(j)->childCount() && !_find)
                    {
                        if(tWidget->topLevelItem(i)->child(j)->child(k)->text(2).toInt() == channel)
                        {
                            channelIndex = k;
                            int l = 0;
                            while(l < tWidget->topLevelItem(i)->child(j)->child(k)->childCount() && !_find)
                            {
                                if(tWidget->topLevelItem(i)->child(j)->child(k)->child(l)->text(2).toInt() == stream)
                                {
                                    streamIndex = l;
                                    int m = 0;
                                    while(m < tWidget->topLevelItem(i)->child(j)->child(k)->child(l)->childCount() && !_find)
                                    {
                                        if(tWidget->topLevelItem(i)->child(j)->child(k)->child(l)->child(m)->text(2) == format)
                                        {
                                            formatIndex = m;
                                            _find = 1;
                                        }
                                        m++;
                                    }
                                }
                                l++;
                            }
                        }
                        k++;
                    }
                }
                j++;
            }
        }
        i++;
    }
    tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->child(streamIndex)->takeChild(formatIndex);
    if(tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->child(streamIndex)->childCount() == 0)
    {
        tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->takeChild(streamIndex);
        if(tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->childCount() == 0)
        {
            tWidget->topLevelItem(serverIndex)->child(cardIndex)->takeChild(channelIndex);
            if(tWidget->topLevelItem(serverIndex)->child(cardIndex)->childCount() == 0)
            {
                tWidget->topLevelItem(serverIndex)->takeChild(cardIndex);
                if(tWidget->topLevelItem(serverIndex)->childCount() == 0)
                {
                    tWidget->takeTopLevelItem(serverIndex);
                }
            }
        }
    }
    return 0;
}
int treewidget::removeStreamItem(QString server, QString videocard, int channel, int stream)
{
    int _find = 0;
    int i = 0;
    int serverIndex = -1;
    int cardIndex = -1;
    int channelIndex = -1;
    int streamIndex = -1;
    while(i < tWidget->topLevelItemCount() && !_find)
    {
        if(tWidget->topLevelItem(i)->text(0) == server)
        {
            serverIndex = i;
            int j = 0;
            while(j < tWidget->topLevelItem(i)->childCount() && !_find)
            {
                if(tWidget->topLevelItem(i)->child(j)->text(2) == videocard)
                {
                    cardIndex = j;
                    int k = 0;
                    while(k < tWidget->topLevelItem(i)->child(j)->childCount() && !_find)
                    {
                        if(tWidget->topLevelItem(i)->child(j)->child(k)->text(2).toInt() == channel)
                        {
                            channelIndex = k;
                            int l = 0;
                            while(l < tWidget->topLevelItem(i)->child(j)->child(k)->childCount() && !_find)
                            {
                                if(tWidget->topLevelItem(i)->child(j)->child(k)->child(l)->text(2).toInt() == stream)
                                {
                                    streamIndex = l;
                                    _find = 1;
                                }
                                l++;
                            }
                        }
                        k++;
                    }
                }
                j++;
            }
        }
        i++;
    }
    tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->takeChild(streamIndex);
    if(tWidget->topLevelItem(serverIndex)->child(cardIndex)->child(channelIndex)->childCount() == 0)
    {
        tWidget->topLevelItem(serverIndex)->child(cardIndex)->takeChild(channelIndex);
        if(tWidget->topLevelItem(serverIndex)->child(cardIndex)->childCount() == 0)
        {
            tWidget->topLevelItem(serverIndex)->takeChild(cardIndex);
            if(tWidget->topLevelItem(serverIndex)->childCount() == 0)
            {
                tWidget->takeTopLevelItem(serverIndex);
            }
        }
    }
    return 0;
}
int treewidget::removeChannelItem(QString server, QString videocard, int channel)
{
    int _find = 0;
    int i = 0;
    int serverIndex = -1;
    int cardIndex = -1;
    int channelIndex = -1;
    while(i < tWidget->topLevelItemCount() && !_find)
    {
        if(tWidget->topLevelItem(i)->text(0) == server)
        {
            serverIndex = i;
            int j = 0;
            while(j < tWidget->topLevelItem(i)->childCount() && !_find)
            {
                if(tWidget->topLevelItem(i)->child(j)->text(2) == videocard)
                {
                    cardIndex = j;
                    int k = 0;
                    while(k < tWidget->topLevelItem(i)->child(j)->childCount() && !_find)
                    {
                        if(tWidget->topLevelItem(i)->child(j)->child(k)->text(2).toInt() == channel)
                        {
                            channelIndex = k;
                            _find = 1;
                        }
                        k++;
                    }
                }
                j++;
            }
        }
        i++;
    }
    tWidget->topLevelItem(serverIndex)->child(cardIndex)->takeChild(channelIndex);
    if(tWidget->topLevelItem(serverIndex)->child(cardIndex)->childCount() == 0)
    {
        tWidget->topLevelItem(serverIndex)->takeChild(cardIndex);
        if(tWidget->topLevelItem(serverIndex)->childCount() == 0)
        {
            tWidget->takeTopLevelItem(serverIndex);
        }
    }
    return 0;
}
int treewidget::removeCardItem(QString server, QString videocard)
{
    int _find = 0;
    int i = 0;
    int serverIndex = -1;
    int cardIndex = -1;
    while(i < tWidget->topLevelItemCount() && !_find)
    {
        if(tWidget->topLevelItem(i)->text(0) == server)
        {
            serverIndex = i;
            int j = 0;
            while(j < tWidget->topLevelItem(i)->childCount() && !_find)
            {
                if(tWidget->topLevelItem(i)->child(j)->text(2) == videocard)
                {
                    cardIndex = j;
                    _find = 1;
                }
                j++;
            }
        }
        i++;
    }
    tWidget->topLevelItem(serverIndex)->takeChild(cardIndex);
    if(tWidget->topLevelItem(serverIndex)->childCount() == 0)
    {
        tWidget->takeTopLevelItem(serverIndex);
    }
    return 0;
}
int treewidget::removeServerItem(QString server)
{
    int _find = 0;
    int i = 0;
    int serverIndex = -1;
    while(i < tWidget->topLevelItemCount() && !_find)
    {
        if(tWidget->topLevelItem(i)->text(0) == server)
        {
            serverIndex = i;
            _find = 1;
        }
        i++;
    }
    tWidget->takeTopLevelItem(serverIndex);
    return 0;
}

int treewidget::reloadTree(QList<serverType> serverList)
{
    for(int i = 0; i < tWidget->topLevelItemCount(); i++)
    {
        tWidget->takeTopLevelItem(i);
    }
    for(int i = 0; i < serverList.count(); i++)
    {
        this->addServerItem(serverList.at(i));
    }
    return 0;
}

QStringList treewidget::getCurrentItemInfo()
{
    QString ipAdd;
    QString cardname;
    QString channelID;
    QString streamID;
    QString codec;
    QStringList list;
    if(tWidget->currentItem()->text(1) == "Format")
    {
        codec = tWidget->currentItem()->text(2);
        streamID = tWidget->currentItem()->parent()->text(2);
        channelID = tWidget->currentItem()->parent()->parent()->text(2);
        cardname = tWidget->currentItem()->parent()->parent()->parent()->text(2);
        ipAdd = tWidget->currentItem()->parent()->parent()->parent()->parent()->text(0);
        list.append(ipAdd);
        list.append(cardname);
        list.append(channelID);
        list.append(streamID);
        list.append(codec);
    }
    else
    {
        if(tWidget->currentItem()->text(1) == "Stream")
        {
            streamID = tWidget->currentItem()->text(2);
            channelID = tWidget->currentItem()->parent()->text(2);
            cardname = tWidget->currentItem()->parent()->parent()->text(2);
            ipAdd = tWidget->currentItem()->parent()->parent()->parent()->text(0);
            list.append(ipAdd);
            list.append(cardname);
            list.append(channelID);
            list.append(streamID);
        }
        else
        {
            if(tWidget->currentItem()->text(1) == "Channel")
            {
                channelID = tWidget->currentItem()->text(2);
                cardname = tWidget->currentItem()->parent()->text(2);
                ipAdd = tWidget->currentItem()->parent()->parent()->text(0);
                list.append(ipAdd);
                list.append(cardname);
                list.append(channelID);
            }
            else
            {
                if(tWidget->currentItem()->text(1) == "Video Card")
                {
                    cardname = tWidget->currentItem()->text(2);
                    ipAdd = tWidget->currentItem()->parent()->text(0);
                    list.append(ipAdd);
                    list.append(cardname);
                }
                else
                {
                    ipAdd = tWidget->currentItem()->text(0);
                    list.append(ipAdd);
                }
            }
        }
    }
    return list;
}
