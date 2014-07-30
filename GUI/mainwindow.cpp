#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menuBar = new menubar();
    this->setMenuBar(menuBar->menuBar);
    treeWidget = new treewidget();
    centralWidget = new centralwidget();
    errorWidget = new errorwidget();
    _fctrl = new filecontrol();
    QWidget* widget = new QWidget();
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(treeWidget->projectWidget,0,0,1,1);
    layout->addWidget(centralWidget->centralWidget,0,1,1,2);
    layout->addWidget(errorWidget->errorWidget,0,3,1,1);
    widget->setLayout(layout);
    this->setCentralWidget(widget);
    this->setWindowTitle("Capture Control");
    this->setWindowIcon(QIcon(":resource/logo.png"));

    setConnect();
}

void MainWindow::setConnect()
{
    connect(menuBar->openAct, SIGNAL(triggered()), this, SLOT(openServerSlot()));
    connect(menuBar->closeAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(menuBar->addAct, SIGNAL(triggered()), this, SLOT(addActSlot()));

    connect(treeWidget->addButton, SIGNAL(clicked()), this, SLOT(addActSlot()));
    connect(treeWidget->minusButton, SIGNAL(clicked()), this, SLOT(removeSlot()));
    connect(treeWidget->refreshButton, SIGNAL(clicked()), this, SLOT(reloadSlot()));
    connect(treeWidget->tWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(treeItemDoubleClickedSlot()));
    connect(treeWidget->tWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(setCopyEnabledSlot(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(this, SIGNAL(hasCopy(int)), this, SLOT(setPasteEnabledSlot(int)));

    connect(menuBar->serverEditAct, SIGNAL(triggered()), this, SLOT(serverEditActSlot()));
    connect(menuBar->streamEditAct, SIGNAL(triggered()), this, SLOT(streamEditActSlot()));
    connect(menuBar->formatEditAct, SIGNAL(triggered()), this, SLOT(formatEditActSlot()));
    connect(menuBar->copyAct, SIGNAL(triggered()), this, SLOT(copySlot()));
    connect(menuBar->pasteAct, SIGNAL(triggered()), this, SLOT(pasteSlot()));
    connect(menuBar->removeAct, SIGNAL(triggered()), this, SLOT(removeSlot()));

    connect(this, SIGNAL(hasTree(bool)), this, SLOT(setAddActEnabled(bool)));
    connect(this, SIGNAL(hasTree(bool)), this, SLOT(setTreeButtonsEnabled(bool)));
}

int MainWindow::addFormatToServerList(serverType _server, streamtype _stream, formatType _format)
{
    int streamIndex = -1;
    int formatIndex = -1;
    int serverIndex = -1;
    int i = 0;
    while(serverIndex == -1 && i < serverList.count())
    {
        if(serverList.at(i).ipAdd == _server.ipAdd)
        {
            serverIndex = i;
            int j = 0;
            while(streamIndex == -1 && j < serverList.at(i).streamList.count())
            {
                if(serverList.at(i).streamList.at(j).streamID == _stream.streamID)
                {
                    streamIndex = j;
                    int k = 0;
                    while(formatIndex == -1 && k < serverList.at(i).streamList.at(j).formatList.count())
                    {
                        if(serverList.at(i).streamList.at(j).formatList.at(k).codec == _format.codec)
                        {
                            formatIndex = k;
                        }
                        k++;
                    }
                }
                j++;
            }
        }
        i++;
    }
    if(formatIndex != -1)
    {
        return 0;
    }
    else
    {
        if(streamIndex == -1)
        {
            _stream.formatList.append(_format);
            this->serverList[serverIndex].streamList.append(_stream);
            return 1;
        }
        else
        {
            this->serverList[serverIndex].streamList[streamIndex].formatList.append(_format);
            return 2;
        }
    }
}

int MainWindow::removeFormat(QString _server, QString _card, int channel, int stream, QString codec)
{
    _fctrl->setFile(_server, 1);
    _fctrl->removeFormat(_server, QString("%1").arg(channel), QString("%1").arg(stream), codec);
    treeWidget->removeFormatItem(_server, _card, channel, stream, codec);
    if(treeWidget->tWidget->topLevelItemCount() == 0)
    {
        emit hasTree(false);
    }
    else emit hasTree(true);
    int _find = 0;
    int i = 0;
    int serverIndex = -1;
    int streamIndex = -1;
    int formatIndex = -1;
    while(!_find && i < serverList.count())
    {
        if(serverList.at(i).ipAdd == _server)
        {
            serverIndex = i;
            int j = 0;
            while(!_find && j < serverList.at(i).streamList.count())
            {
                if(serverList.at(i).streamList.at(j).streamID == stream)
                {
                    streamIndex = j;
                    int k = 0;
                    while(!_find && k < serverList.at(i).streamList.at(j).formatList.count())
                    {
                        if(serverList.at(i).streamList.at(j).formatList.at(k).codec == codec)
                        {
                            formatIndex = k;
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
    serverList[serverIndex].streamList[streamIndex].formatList.removeAt(formatIndex);
    if(serverList.at(serverIndex).streamList[streamIndex].formatList.count() == 0)
    {
        serverList[serverIndex].streamList.removeAt(streamIndex);
        if(serverList.at(serverIndex).streamList.count() == 0)
        {
            serverList.removeAt(serverIndex);
        }
    }

    return 0;
}

int MainWindow::removeStream(QString _server, QString _card, int channel, int stream)
{
    _fctrl->setFile(_server, 1);
    _fctrl->removeStream(_server, QString("%1").arg(channel), QString("%1").arg(stream));
    treeWidget->removeStreamItem(_server, _card, channel, stream);
    if(treeWidget->tWidget->topLevelItemCount() == 0)
    {
        emit hasTree(false);
    }
    else emit hasTree(true);
    int _find = 0;
    int i = 0;
    int serverIndex = -1;
    int streamIndex = -1;
    while(!_find && i < serverList.count())
    {
        if(serverList.at(i).ipAdd == _server)
        {
            int j = 0;
            serverIndex = i;
            while(!_find && j < serverList.at(i).streamList.count())
            {
                if(serverList.at(i).streamList.at(j).streamID == stream)
                {
                    _find = 1;
                    streamIndex = 1;
                }
            }
        }
    }
    serverList[serverIndex].streamList.removeAt(streamIndex);
    if(serverList[serverIndex].streamList.count() == 0)
    {
        serverList.removeAt(serverIndex);
    }
    return 0;
}
int MainWindow::removeChannel(QString _server, QString _card, int channel)
{
    _fctrl->setFile(_server, 1);
    _fctrl->removeChannel(_server, QString("%1").arg(channel));
    treeWidget->removeChannelItem(_server, _card, channel);
    if(treeWidget->tWidget->topLevelItemCount() == 0)
    {
        emit hasTree(false);
    }
    else emit hasTree(true);
    for(int i = 0; i < serverList.count(); i++)
    {
        if(serverList.at(i).ipAdd == _server)
        {
            for(int j = 0; j < serverList.at(i).streamList.count(); j++)
            {
                if(serverList.at(i).streamList.at(j).channel == channel)
                {
                    serverList[i].streamList.removeAt(j);
                }
            }
        }
        if(serverList[i].streamList.count() == 0)
        {
            serverList.removeAt(i);
            i = i - 1;
        }
    }
    return 0;
}
int MainWindow::removeCard(QString _server, QString _card)
{
    _fctrl->setFile(_server, 1);
    QList<cardtype> cardList = _fctrl->readVideoChannelFile();
    for(int i = 0; i < cardList.count(); i++)
    {
        for(int j = 0; j < cardList.at(i).channelList.count(); j++)
        {
            _fctrl->removeChannel(_server, QString("%1").arg(cardList.at(i).channelList.at(j)));
        }
    }
    treeWidget->removeCardItem(_server, _card);
    if(treeWidget->tWidget->topLevelItemCount() == 0)
    {
        emit hasTree(false);
    }
    else emit hasTree(true);
    QList<int> channelList;
    for(int i = 0; i < cardList.count(); i++)
    {
        for(int j = 0; j < cardList.at(i).channelList.count(); j++)
        {
            channelList.append(cardList.at(i).channelList.at(j));
        }
    }
    for(int i = 0; i < serverList.count(); i++)
    {
        for(int j = 0; j < serverList.at(i).streamList.count(); j++)
        {
            if(channelList.contains(serverList.at(i).streamList.at(j).channel))
            {
                serverList[i].streamList.removeAt(j);
                j--;
            }
        }
        if(serverList.at(i).streamList.count() == 0)
        {
            serverList.removeAt(i);
            i--;
        }
    }
    return 0;
}

int MainWindow::removeServer(QString _server)
{
    treeWidget->removeServerItem(_server);
    errorWidget->removeServer(_server);
    if(treeWidget->tWidget->topLevelItemCount() == 0)
    {
        emit hasTree(false);
    }
    else emit hasTree(true);
    int _find = 0;
    int i = 0;
    while(!_find && i < serverList.count())
    {
        if(serverList.at(i).ipAdd == _server)
        {
            _find = 1;
            serverList.removeAt(i);
        }
        i++;
    }
    return 0;
}

/////////////////////////SLOTS////////////////////////////////////
void MainWindow::openServerSlot()
{
    _openServerDialog = new openServerDialog();
    connect(_openServerDialog->okButton, SIGNAL(clicked()), this, SLOT(addServerSlot()));
    _openServerDialog->openServer->show();
}

void MainWindow::addActSlot()
{
    _addDialog = new addDialog();
    _addDialog->setServerListSlot(serverList);
    connect(_addDialog->okButton, SIGNAL(clicked()), this, SLOT(addStreamSlot()));
    _addDialog->dialog->exec();
}

void MainWindow::serverEditActSlot()
{
    if(treeWidget->tWidget->topLevelItemCount() > 0)
    {
        editIndex.clear();
        QString ipAdd;
#ifdef _WIN32_
        if(treeWidget->tWidget->currentItem()->text(0).split(".") == 4)
#elif __linux__
        if(treeWidget->tWidget->currentItem()->text(0) == "Local" || treeWidget->tWidget->currentItem()->text(0) == "local")
#endif
        {
            ipAdd = treeWidget->tWidget->currentItem()->text(0);
        }
        else
        {
            if(treeWidget->tWidget->currentItem()->text(1) == "Video Card")
            {
                ipAdd = treeWidget->tWidget->currentItem()->parent()->text(0);
            }
            else
            {
                if(treeWidget->tWidget->currentItem()->text(1) == "Channel")
                {
                    ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->text(0);
                }
                else
                {
                    if(treeWidget->tWidget->currentItem()->text(1) == "Stream")
                    {
                        ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->text(0);
                    }
                    else
                    {
                        ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->parent()->text(0);
                    }
                }
            }
        }
        _serverEditDialog = new serverEditDialog(ipAdd);
        _serverEditDialog->okButton->setEnabled(false);
        int serverIndex = -1;
        int i = 0;
        while(serverIndex == -1 && i < serverList.count())
        {
            if(serverList.at(i).ipAdd == ipAdd)
            {
                serverIndex = i;
            }
            i++;
        }
        editIndex.append(serverIndex);
        _serverEditDialog->projectNameEdit->setText(serverList.at(serverIndex).projectName);
        connect(_serverEditDialog->projectNameEdit, SIGNAL(textChanged(QString)), _serverEditDialog, SLOT(setOKButtonEnable()));
        _serverEditDialog->serverNameEdit->setText(serverList.at(serverIndex).serverName);
        connect(_serverEditDialog->serverNameEdit, SIGNAL(textChanged(QString)), _serverEditDialog, SLOT(setOKButtonEnable()));
        QList<cardtype> cardList = serverList.at(serverIndex).cardList;
        for(i = 0; i < cardList.count(); i++)
        {
            QTableWidgetItem* cardIndexitem = new QTableWidgetItem(QString("%1").arg(cardList.at(i).index));

            QTableWidgetItem* cardNameitem = new QTableWidgetItem(cardList.at(i).name);
            QString channels;
            for(int j = 0; j < cardList.at(i).channelList.count(); j++)
            {
                channels += QString("%1 ").arg(cardList.at(i).channelList.at(j));
            }
            channels.chop(1);
            QTableWidgetItem* channelItem = new QTableWidgetItem(channels);
            _serverEditDialog->videoCardTable->setItem(i, 0, cardIndexitem);
            _serverEditDialog->videoCardTable->setItem(i, 1, cardNameitem);
            _serverEditDialog->videoCardTable->setItem(i, 2, channelItem);
        }
        connect(_serverEditDialog->videoCardTable, SIGNAL(cellChanged(int,int)), _serverEditDialog, SLOT(setOKButtonEnable()));
        connect(_serverEditDialog->okButton, SIGNAL(clicked()), this, SLOT(serverEditChangedSlot()));
        _serverEditDialog->dialog->exec();
    }
}

void MainWindow::streamEditActSlot()
{
    if(treeWidget->tWidget->topLevelItemCount() > 0)
    {
        editIndex.clear();
        QString ipAdd, streamID;
        if(treeWidget->tWidget->currentItem()->text(1) == "Channel")
        {
            ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->text(0);
            streamID = treeWidget->tWidget->currentItem()->child(0)->text(2);
        }
        else
        {
            if(treeWidget->tWidget->currentItem()->text(1) == "Stream")
            {
                ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->text(0);
                streamID = treeWidget->tWidget->currentItem()->text(2);
            }
            else
            {
                if(treeWidget->tWidget->currentItem()->text(1) == "Format")
                {
                    ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->parent()->text(0);
                    streamID = treeWidget->tWidget->currentItem()->parent()->text(2);
                }
            }
        }
        if(!ipAdd.isEmpty() && !streamID.isEmpty())
        {
            QString _s = QString("Stream %1").arg(streamID);
            _streamEditDialog = new streameditdialog(ipAdd, _s);
            _streamEditDialog->okButton->setEnabled(false);
            int serverIndex = -1;
            int streamIndex = -1;
            int i = 0;
            while(i < serverList.count() && serverIndex == -1)
            {
                if(serverList.at(i).ipAdd == ipAdd)
                {
                    serverIndex = i;
                    int j = 0;
                    while(j < serverList.at(i).streamList.count() && streamIndex == -1)
                    {
                        if(serverList.at(i).streamList.at(j).streamID == streamID.toInt())
                        {
                            streamIndex = j;
                        }
                        j++;
                    }
                }
                i++;
            }
            editIndex.append(serverIndex);
            editIndex.append(streamIndex);
            _streamEditDialog->setStream2Table(serverList.at(serverIndex).streamList.at(streamIndex));
            connect(_streamEditDialog->okButton, SIGNAL(clicked()), this, SLOT(streamEditChangedSlot()));
            _streamEditDialog->dialog->exec();
        }
    }
}

void MainWindow::formatEditActSlot()
{
    if(treeWidget->tWidget->topLevelItemCount() > 0)
    {
        editIndex.clear();
        QString ipAdd, streamID, codec;
        if(treeWidget->tWidget->currentItem()->text(1) == "Format")
        {
            ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->parent()->text(0);
            streamID = treeWidget->tWidget->currentItem()->parent()->text(2);
            codec = treeWidget->tWidget->currentItem()->text(2);
        }
        if(!ipAdd.isEmpty() && !streamID.isEmpty() && !codec.isEmpty())
        {
            QString _s = QString("Stream %1").arg(streamID);
            QString _s1 = QString("Codec %1").arg(codec);
            _formatEditDialog = new formateditdialog(ipAdd, _s, _s1);
            _formatEditDialog->okButton->setEnabled(false);
            int serverIndex = -1;
            int streamIndex = -1;
            int formatIndex = -1;
            int i = 0;
            while(i < serverList.count() && serverIndex == -1)
            {
                if(serverList.at(i).ipAdd == ipAdd)
                {
                    serverIndex = i;
                    int j = 0;
                    while(j < serverList.at(i).streamList.count() && streamIndex == -1)
                    {
                        if(serverList.at(i).streamList.at(j).streamID == streamID.toInt())
                        {
                            streamIndex = j;
                            int k = 0;
                            while(k < serverList.at(i).streamList.at(j).formatList.count() && formatIndex == -1)
                            {
                                if(serverList.at(i).streamList.at(j).formatList.at(k).codec == codec)
                                {
                                    formatIndex = k;
                                }
                                k++;
                            }
                        }
                        j++;
                    }
                }
                i++;
            }
            editIndex.append(serverIndex);
            editIndex.append(streamIndex);
            editIndex.append(formatIndex);
            _formatEditDialog->setFormat2Table(serverList.at(serverIndex).streamList.at(streamIndex).formatList.at(formatIndex));
            connect(_formatEditDialog->okButton, SIGNAL(clicked()), this, SLOT(formatEditChangedSlot()));
            _formatEditDialog->dialog->exec();
        }

    }
}

void MainWindow::addServerSlot()
{
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////in addServerSlot() needs to do following things
    ///1. get ipAdd
    ///1. test files: config.xml, status.xml, dvs_sdi.log, uberecorder.conf
    ///2. def: def the project name, server name, ipAdd in servertype, if config.xml is not exsit, set new config.xml in server
    ///3. initial the servertype
    ///4. read config.xml, set the servertype, add the sub-types in the type
    ///5. add component items in treewidget, errorwidget
    //////////////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32_
    if(!_openServerDialog->serverEdit->text().split(".").at(0).isEmpty)
#elif linux
    if(!_openServerDialog->serverEdit->text().isEmpty())
#endif
    {
        QString ipAdd = _openServerDialog->serverEdit->text();
        _fctrl->setFile(ipAdd);
        //while(_fctrl->serverID.isEmpty()){};
        QList< int> isServer = _fctrl->isServer();
        if(isServer.count() == 1)
        {
            QMessageBox msg;
            msg.setWindowIcon(QIcon(":resource/logo.png"));
            msg.setWindowTitle(QString("Error"));
            msg.setText("Error, can not connet to server");
        }
        if(isServer.contains(0))
        {
            QString text;
            for(int i = 0; i < isServer.count(); i++)
            {
                if(isServer.at(i) == 0)
                {
                    if(i == 0)
                    {
                        text.append("Config file is not exists, initial a new config file.\n");
                        _fctrl->iniConfigFile();
                    }
                    if(i == 1)
                        text.append("Status file is not exists, please connect to the support.\n");
                    if(i == 2)
                    {
                        text.append("vc.conf does not find, initial a new video card config file with only one video card.\n");
                        _fctrl->iniVideoChannelFile();
                    }
                    if(i == 3)
                    {
                        text.append("uberecorder.conf does not find, can not get the server name.\n");
                    }
                    if(i == 4)
                    {
                        text.append("dvs_sdi.log does not find, can not update the error.\n");
                    }
                }
            }
            QMessageBox msg;
            msg.setWindowIcon(QIcon(":resource/logo.png"));
            msg.setWindowTitle(QString("Error"));
            msg.setText(text);
        }
        serverType server = _fctrl->readConfigFile();
        server.serverName = _fctrl->readUberecorderFile();
        int _isFind = 0;
        int i = 0;
        while(!_isFind && i < serverList.count())
        {
            if(serverList.at(i).ipAdd == server.ipAdd)
            {
                _isFind = 1;
            }
            i++;
        }
        if(!_isFind)
        {
            treeWidget->addServerItem(server);
            errorWidget->addTreeItem(server);
            serverList.append(server);
        }

        emit _openServerDialog->cancelButton->clicked();
        if(treeWidget->tWidget->topLevelItemCount() > 0)
        {
            emit hasTree(true);
        }
        else
        {
            emit hasTree(false);
        }
    }
}

void MainWindow::setAddActEnabled(bool hasTree)
{
    menuBar->addAct->setEnabled(hasTree);
    treeWidget->addButton->setEnabled(hasTree);
    treeWidget->minusButton->setEnabled(hasTree);
    treeWidget->refreshButton->setEnabled(hasTree);
}

void MainWindow::addStreamSlot()
{
    serverType _server;
    _server.ipAdd = _addDialog->ipEdit->currentText();
    _server.serverName = _addDialog->serverNameEdit->text();
    _server.projectName = _addDialog->projectNameEdit->text();
    streamtype _stream;
    _stream.aspect = _addDialog->aspectEdit->currentText();
    _stream.audioTrack = _addDialog->audioEdit->text().toInt();
    _stream.channel = _addDialog->channelEdit->value();
    _stream.enable = 1;
    _stream.restart = 0;
    _stream.split = _addDialog->splitEdit->value();
    _stream.streamID = _addDialog->streamEdit->text().toInt();
    _stream.thumb = _addDialog->thumEdit->isChecked();
    _stream.thumPPS = _addDialog->thumPPSEdit->value();
    formatType _format;
    _format.archivPath = _addDialog->archivPathEdit->text();
    _format.archivResultPath = _addDialog->archivResultEdit->text();
    _format.codec = _addDialog->codecEdit->currentText();
    _format.creatingPath = _addDialog->creatingpathEdit->text();
    _format.fileName = _addDialog->fileNameEdit->text();
    if(_addDialog->codecEdit->currentIndex() > 17)
    {
        _format.scale = _addDialog->scaleEdit->text();
        _format.audioBit = _addDialog->audioBitEdit->text().toInt();
        _format.videoBit = _addDialog->videoBitEdit->text().toInt();
    }
    _format.tapeName = _addDialog->tapeNameEdit->text();
    _format.timeOverlay = 0;

    int _add = this->addFormatToServerList(_server, _stream, _format);
    if(_add == 0)
    {
        QMessageBox msg;
        msg.setText("The codec has fund in the project");
        msg.setWindowTitle("Add Error");
        msg.setWindowIcon(QIcon(":resource/logo.png"));
        msg.exec();
    }
    else
    {
        QString cardName;
        int _find = 0;
        for(int i = 0; i < serverList.count() && !_find; i++)
        {
            for(int j = 0; j < serverList.at(i).cardList.count() && !_find; j++)
            {
                for(int k = 0; k < serverList.at(i).cardList.at(j).channelList.count() && !_find; k++)
                {
                    if(serverList.at(i).cardList.at(j).channelList.at(k) == _stream.channel)
                    {
                        _find = 1;
                        cardName = serverList.at(i).cardList.at(j).name;
                    }
                }
            }
        }
        treeWidget->addFormatItem(_server, cardName, _stream, _format, _add);
        errorWidget->addTreeItem(_server.ipAdd, cardName, _stream.channel, _stream.streamID);
        _fctrl->writeFormattoXML(_server, _stream, _format);
    }
    emit _addDialog->cancelButton->clicked();
}


void MainWindow::removeSlot()
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item = treeWidget->tWidget->currentItem();
    if(item->text(1) == "Format")
    {
        QString codec = item->text(2);
        int streamID = item->parent()->text(2).toInt();
        int channelID = item->parent()->parent()->text(2).toInt();
        QString card = item->parent()->parent()->parent()->text(2);
        QString ipAdd = item->parent()->parent()->parent()->parent()->text(0);
        this->removeFormat(ipAdd, card, channelID, streamID, codec);
    }
    else
    {
        if(item->text(1) == "Stream")
        {
            int streamID = item->text(2).toInt();
            int channelID = item->parent()->text(2).toInt();
            QString card = item->parent()->parent()->text(2);
            QString ipAdd = item->parent()->parent()->parent()->text(0);
            this->removeStream(ipAdd, card, channelID, streamID);
        }
        else
        {
            if(item->text(1) == "Channel")
            {
                int channelID = item->text(2).toInt();
                QString card = item->parent()->text(2);
                QString ipAdd = item->parent()->parent()->text(0);
                this->removeChannel(ipAdd, card, channelID);
            }
            else
            {
                if(item->text(1) == "Video Card")
                {
                    QString card = item->text(2);
                    QString ipAdd = item->parent()->text(0);
                    this->removeCard(ipAdd, card);
                }
                else
                {
#ifdef _WIN32_
                    if(item->text(0).split(".") == 4)
#elif linux
                    if(item->text(0) == "Local")
#endif
                    {
                        QString ipAdd = item->text(0);
                        this->removeServer(ipAdd);
                    }
                }
            }
        }
    }
}


void MainWindow::setTreeButtonsEnabled(bool hasTree)
{
    treeWidget->addButton->setEnabled(hasTree);
    treeWidget->minusButton->setEnabled(hasTree);
    treeWidget->refreshButton->setEnabled(hasTree);
    menuBar->removeAct->setEnabled(hasTree);
}

void MainWindow::reloadSlot()
{
    treeWidget->reloadTree(serverList);
    if(treeWidget->tWidget->topLevelItemCount()> 0)
        emit hasTree(true);
    else
        emit hasTree(false);
}

void MainWindow::treeItemDoubleClickedSlot()
{
    QStringList list = treeWidget->getCurrentItemInfo();
    QString ipAdd = list.at(0);
    bool _find = 0;
    int i = 0;
    int serverIndex = -1;
    while(!_find && i < serverList.count())
    {
        if(serverList.at(i).ipAdd == ipAdd)
        {
            _find = 1;
            serverIndex = i;
        }
        i++;
    }
    ///////Format tree item
    if(list.count() == 5)
    {
        //QString cardname = list.at(1);
        //QString channelID = list.at(2);
        QString streamID = list.at(3);
        QString codec = list.at(4);

        i = 0;
        int streamIndex = -1;
        int formatIndex = -1;
        while(streamIndex == -1 && i < serverList.at(serverIndex).streamList.count())
        {
            if(serverList.at(serverIndex).streamList.at(i).streamID == streamID.toInt())
            {
                streamIndex = i;
                int j = 0;
                while(formatIndex == -1 && j < serverList.at(serverIndex).streamList.at(i).formatList.count())
                {
                    if(serverList.at(serverIndex).streamList.at(i).formatList.at(j).codec == codec)
                    {
                        formatIndex = j;
                    }
                    j++;
                }
            }
            i++;
        }

        centralWidget->setData(serverList.at(serverIndex), serverList.at(serverIndex).streamList.at(streamIndex), serverList.at(serverIndex).streamList.at(streamIndex).formatList.at(formatIndex));
    }
    /////Stream tree item///////
    if(list.count() == 4)
    {
        //QString cardname = list.at(1);
        //QString channelID = list.at(2);
        QString streamID = list.at(3);
        i = 0;
        int streamIndex = -1;
        while(streamIndex == -1 && i < serverList.at(serverIndex).streamList.count())
        {
            if(serverList.at(serverIndex).streamList.at(i).streamID == streamID.toInt())
            {
                streamIndex = i;
            }
            i++;
        }
        centralWidget->setData(serverList.at(serverIndex), serverList.at(serverIndex).streamList.at(streamIndex));
    }
    //////Channel tree item////////
    if(list.count() == 3)
    {
        //QString cardname = list.at(1);
        QString channelID = list.at(2);
        i = 0;
        int streamIndex = -1;
        while(streamIndex == -1 && i < serverList.at(serverIndex).streamList.count())
        {
            if(serverList.at(serverIndex).streamList.at(i).channel == channelID.toInt())
            {
                streamIndex = i;
            }
            i++;
        }
        serverType _server = serverList.at(serverIndex);
        streamtype _stream = _server.streamList.at(streamIndex);
        centralWidget->setData(_server, _stream);
    }
    if(list.count() == 2)
    {
        QString cardname = list.at(1);
        QList<cardtype> cardList = serverList.at(serverIndex).cardList;
        int channelID = -1;
        i = 0;
        while(i < cardList.count() && channelID == -1)
        {
            if(cardList.at(i).name == cardname)
            {
                channelID = cardList.at(i).channelList.at(0);
            }
            i++;
        }
        int streamIndex = -1;
        i = 0;
        while(streamIndex == -1 && i < serverList.at(serverIndex).streamList.count())
        {
            if(serverList.at(serverIndex).streamList.at(i).channel == channelID)
            {
                streamIndex = i;
            }
            i++;
        }
        centralWidget->setData(serverList.at(serverIndex), serverList.at(serverIndex).streamList.at(streamIndex));
    }
    if(list.count() == 1)
    {
        serverType _server = serverList.at(serverIndex);
        centralWidget->setData(_server);
    }
}

void MainWindow::serverEditChangedSlot()
{
    QString servername = _serverEditDialog->serverNameEdit->text();
    QString projectname = _serverEditDialog->projectNameEdit->text();
    QList<cardtype> cardList;
    cardList = _serverEditDialog->table2CardList();
    int serverIndex = editIndex.at(0);
    if(servername != serverList.at(serverIndex).serverName)
    {
        _fctrl->setFile(serverList.at(serverIndex).ipAdd, 1);
        _fctrl->setServerName(servername);
        serverList[serverIndex].serverName = servername;
    }
    if(projectname != serverList.at(serverIndex).projectName)
    {
        _fctrl->setFile(serverList.at(serverIndex).ipAdd, 1);
        _fctrl->setProjectName(projectname);
        serverList[serverIndex].projectName = projectname;
    }
    int sameCardList = 1;
    int i = 0;
    if(cardList.count() != serverList.at(serverIndex).cardList.count())
    {
        sameCardList = 0;
    }
    while(sameCardList && i < serverList.at(serverIndex).cardList.count())
    {
        cardtype _card = serverList[serverIndex].cardList[i];
        sameCardList = cardList[i].compare(_card);
        i++;
    }
    if(!sameCardList)
    {
        _fctrl->setFile(serverList.at(serverIndex).ipAdd, 1);
        _fctrl->writeVideoChannelFile(cardList);
        serverList[serverIndex].cardList = cardList;
    }
    _serverEditDialog->dialog->close();
    this->reloadSlot();
}

void MainWindow::streamEditChangedSlot()
{
    streamtype currentStream;
    currentStream.aspect = _streamEditDialog->aspectEdit->currentText();
    currentStream.audioTrack = _streamEditDialog->audioEdit->value();
    currentStream.channel = _streamEditDialog->channelEdit->value();
    currentStream.enable = _streamEditDialog->enableEdit->isChecked();
    currentStream.formatList = serverList.at(editIndex.at(0)).streamList.at(editIndex.at(1)).formatList;
    currentStream.projectNr = _streamEditDialog->projectNrEdit->value();
    currentStream.restart = _streamEditDialog->restartEdit->isChecked();
    currentStream.split = _streamEditDialog->splitEdit->value();
    currentStream.streamID = _streamEditDialog->streamEdit->value();
    currentStream.thumb = _streamEditDialog->thumEdit->isChecked();
    currentStream.thumPPS = _streamEditDialog->thumPPSEdit->value();

    streamtype preStream = serverList.at(editIndex.at(0)).streamList.at(editIndex.at(1));

    ///////////if the streamID and channel is not changed
    if(currentStream.channel == preStream.channel && currentStream.streamID == preStream.streamID)
    {
        serverList[editIndex.at(0)].streamList.replace(editIndex.at(1), currentStream);
        _fctrl->setFile(serverList.at(editIndex.at(0)).ipAdd, 1);
        _fctrl->streamEdittoXML(preStream, currentStream);
    }
    /////////////if the streamID or channel is changed
    else
    {
        /////////////////////test, whether the streamID is existed in the serverList.
        int streamIndex = -1;
        int i = 0;
        while(streamIndex == -1 && i < serverList.at(editIndex.at(0)).streamList.count())
        {
            if(serverList.at(editIndex.at(0)).streamList.at(i).channel == currentStream.channel && serverList.at(editIndex.at(0)).streamList.at(i).streamID == currentStream.streamID)
            {
                streamIndex = i;
            }
            i++;
        }
        //////////////////////the StreamID is existed in the serverList. Popout a messageBox, stop the edition
        if(streamIndex != -1)
        {
            QMessageBox msg;
            msg.setWindowIcon(QIcon(":resource/icon.png"));
            msg.setWindowTitle("Same Stream find");
            msg.setText("The stream with same stream id is already existed. Edit error");
            msg.exec();
        }
        /////////////////////the stream is not existed in the serverList
        else
        {
            serverList[editIndex.at(0)].streamList.replace(editIndex.at(1), currentStream);
            _fctrl->setFile(serverList.at(editIndex.at(0)).ipAdd, 1);
            _fctrl->streamEdittoXML(preStream, currentStream);
        }
    }
    _streamEditDialog->dialog->close();
    this->reloadSlot();
}

void MainWindow::formatEditChangedSlot()
{
    formatType currentFormat;
    currentFormat.archivPath = _formatEditDialog->archivPathEdit->text();
    currentFormat.archivResultPath = _formatEditDialog->archivResultEdit->text();
    currentFormat.codec = _formatEditDialog->codecEdit->currentText();
    currentFormat.creatingPath = _formatEditDialog->creatingpathEdit->text();
    currentFormat.fileName = _formatEditDialog->fileNameEdit->text();
    if(_formatEditDialog->codecEdit->currentIndex() > 17)
    {
        currentFormat.scale = _formatEditDialog->scaleEdit->text();
        currentFormat.audioBit = _formatEditDialog->audioBitEdit->text().toInt();
        currentFormat.videoBit = _formatEditDialog->videoBitEdit->text().toInt();
    }
    currentFormat.tapeName = _formatEditDialog->tapeNameEdit->text();
    currentFormat.timeOverlay = _formatEditDialog->timeoverlayEdit->value();

    formatType preFormat = serverList.at(editIndex.at(0)).streamList.at(editIndex.at(1)).formatList.at(editIndex.at(2));
    if(currentFormat.codec == preFormat.codec)
    {
        serverList[editIndex.at(0)].streamList[editIndex.at(1)].formatList.replace(editIndex.at(2), currentFormat);
        _fctrl->setFile(serverList.at(editIndex.at(0)).ipAdd, 1);
        _fctrl->formatEdittoXML(serverList.at(editIndex.at(0)).streamList.at(editIndex.at(1)), preFormat, currentFormat);
    }
    else
    {
        int _find = 0;
        int i = 0;
        while(!_find && i < serverList.at(editIndex.at(0)).streamList.at(editIndex.at(1)).formatList.count())
        {
            if(serverList.at(editIndex.at(0)).streamList.at(editIndex.at(1)).formatList.at(i).codec == currentFormat.codec)
            {
                _find = 1;
            }
            i++;
        }
        if(_find)
        {
            QMessageBox msg;
            msg.setWindowIcon(QIcon(":resource/icon.png"));
            msg.setWindowTitle("Same Stream find");
            msg.setText("The format with same codec id is already existed. Edit error");
            msg.exec();
        }
        else
        {
            serverList[editIndex.at(0)].streamList[editIndex.at(1)].formatList.replace(editIndex.at(2), currentFormat);
            _fctrl->setFile(serverList.at(editIndex.at(0)).ipAdd, 1);
            _fctrl->formatEdittoXML(serverList.at(editIndex.at(0)).streamList.at(editIndex.at(1)), preFormat, currentFormat);
        }
    }
    _formatEditDialog->dialog->close();
    this->reloadSlot();
}

void MainWindow::copySlot()
{
    if(treeWidget->tWidget->currentItem() != 0)
    {
        if(treeWidget->tWidget->currentItem()->text(1) == "Format")
        {
            QString ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->parent()->text(0);
            QString streamID = treeWidget->tWidget->currentItem()->parent()->text(2);
            QString codec = treeWidget->tWidget->currentItem()->text(2);
            int serverIndex = -1;
            int streamIndex = -1;
            int formatIndex = -1;
            int i = 0;
            while(i < serverList.count() && serverIndex == -1)
            {
                if(serverList.at(i).ipAdd == ipAdd)
                {
                    serverIndex = i;
                    int j = 0;
                    while(j < serverList.at(i).streamList.count() && streamIndex == -1)
                    {
                        if(serverList.at(i).streamList.at(j).streamID == streamID.toInt())
                        {
                            streamIndex = j;
                            int k = 0;
                            while(k < serverList.at(i).streamList.at(j).formatList.count() && formatIndex == -1)
                            {
                                if(serverList.at(i).streamList.at(j).formatList.at(k).codec == codec)
                                {
                                    formatIndex = k;
                                }
                                k++;
                            }
                        }
                        j++;
                    }
                }
                i++;
            }
            _copyFormat = serverList.at(serverIndex).streamList.at(streamIndex).formatList.at(formatIndex);
            if(!_copyFormat.codec.isEmpty())
                emit hasCopy(1);
            else
                emit hasCopy(0);
        }

    }
}


void MainWindow::pasteSlot()
{
    if(treeWidget->tWidget->currentItem() != 0 && !_copyFormat.codec.isEmpty())
    {
        serverType _desServer;
        streamtype _desStream;
        QString cardName;
        QString ipAdd;
        QString streamID;

        if(treeWidget->tWidget->currentItem()->text(1) == "Format")
        {
            ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->parent()->text(0);
            cardName = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->text(2);
            streamID = treeWidget->tWidget->currentItem()->parent()->text(2);
        }
        else
        {
            if(treeWidget->tWidget->currentItem()->text(1) == "Stream")
            {
                ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->parent()->text(0);
                cardName = treeWidget->tWidget->currentItem()->parent()->parent()->text(2);
                streamID = treeWidget->tWidget->currentItem()->text(2);
            }
            else
            {
                if(treeWidget->tWidget->currentItem()->text(1) == "Channel")
                {
                    ipAdd = treeWidget->tWidget->currentItem()->parent()->parent()->text(0);
                    cardName = treeWidget->tWidget->currentItem()->parent()->text(2);
                    streamID = treeWidget->tWidget->currentItem()->child(0)->text(2);
                }
            }
        }
        if(!ipAdd.isEmpty() && !streamID.isEmpty())
        {
            int serverIndex = -1;
            int streamIndex = -1;
            int i = 0;
            while(i < serverList.count() && serverIndex == -1)
            {
                if(serverList.at(i).ipAdd == ipAdd)
                {
                    serverIndex = i;
                    int j = 0;
                    while(j < serverList.at(i).streamList.count() && streamIndex == -1)
                    {
                        if(serverList.at(i).streamList.at(j).streamID == streamID.toInt())
                        {
                            streamIndex = j;
                        }
                        j++;
                    }
                }
                            i++;
            }
            _desServer = serverList.at(serverIndex);
            _desStream = serverList.at(serverIndex).streamList.at(streamIndex);
            addFormatToServerList(_desServer, _desStream, _copyFormat);
            
            treeWidget->addFormatItem(_desServer, cardName, _desStream, _copyFormat, 1);
            _fctrl->writeFormattoXML(_desServer, _desStream, _copyFormat);
            this->reloadSlot();
        }
    }
}

void MainWindow::setCopyEnabledSlot(QTreeWidgetItem* currentItem, QTreeWidgetItem* preItem)
{
    if(currentItem != 0)
    {
        if(currentItem->text(1) == "Format")
        {
            qDebug()<<"Here";
            menuBar->copyAct->setEnabled(true);
        }
        else
        {
            menuBar->copyAct->setEnabled(false);
        }
    }
    else
    {
        menuBar->copyAct->setEnabled(false);
    }
}

void MainWindow::setPasteEnabledSlot(int enabled)
{
    menuBar->pasteAct->setEnabled(enabled);
}

MainWindow::~MainWindow()
{

}
