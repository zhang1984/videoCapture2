#include "filecontrol.h"
#include <GUI/Dialog/streamiddialog.h>

filecontrol::filecontrol()
{
    configFile = new QFile();
    statusFile = new QFile();
    logFile = new QFile();
    uberecorderFile = new QFile();
    videoChannelFile = new QFile();
    orderFile = new QFile();
}

filecontrol::filecontrol(QString ipAdd)
{
    this->ipAdd = ipAdd;
    configFile = new QFile();
    statusFile = new QFile();
    logFile = new QFile();
    uberecorderFile = new QFile();
    videoChannelFile = new QFile();
    orderFile = new QFile();
#ifdef _WIN32_
    serverID = ipAdd.split(".").at(3);
#elif linux
    streamiddialog* dialog = new streamiddialog();
    dialog->dialog->show();
    serverID = dialog->id;
#endif
}

int filecontrol::setFile(QString ipAdd, int noDialog)
{
    this->ipAdd = ipAdd;
    if(configFile->isOpen())
        configFile->close();
    if(statusFile->isOpen())
        statusFile->close();
    if(logFile->isOpen())
        logFile->close();
    if(uberecorderFile->isOpen())
        uberecorderFile->close();
    if(videoChannelFile->isOpen())
        videoChannelFile->close();
    if(orderFile->isOpen())
        orderFile->close();
#ifdef _WIN32_
    configFile->setFileName(QString("%1%2%3").arg("\\\\", this->ipAdd, "/ubecontrol/config.xml"));
    statusFile->setFileName(QString("%1%2%3").arg("\\\\", this->ipAdd, "/ubecontrol/status.xml"));
    videoChannelFile->setFileName(QString("%1%2%3").arg("\\\\", this->ipAdd, "/etc/vc_new.conf"));
    uberecorderFile->setFileName(QString("%1%2%3").arg("\\\\", this->ipAdd, "/etc/uberecorder.conf"));
    logFile->setFileName(QString("%1%2%3").arg("\\\\", this->ipAdd, "/log/dvs_sdi.log"));
    orderFile->setFileName(QString("%1%2%3").arg("\\\\", this->ipAdd, "/ubecontrol/order.xml"));
    serverID = ipAdd.split(".").at(3);
#elif linux
    if(QString::compare("local", this->ipAdd, Qt::CaseInsensitive) == 0)
    {
        configFile->setFileName("/usr/local/ubecontrol/config.xml");
        statusFile->setFileName("/usr/local/ubecontrol/status.xml");
        videoChannelFile->setFileName("/usr/local/etc/vc_new.conf");
        uberecorderFile->setFileName("/usr/local/etc/uberecorder.conf");
        logFile->setFileName("/Storage/log/dvs_sdi.log");
        orderFile->setFileName("/usr/local/ubecontrol/order.xml");
        if(!noDialog)
        {
            streamiddialog* dialog = new streamiddialog();
            dialog->dialog->exec();
            serverID = dialog->id;
        }
    }
#endif
    return 0;
}

QList< int> filecontrol::isServer()
{
    QList< int> _return;
#ifdef _WIN32_
    if(QDir(QString("%1%2%3").arg("\\\\", this->ipAdd, "/ubecontrol/")).exists() &&
            QDir(QString("%1%2%3").arg("\\\\", this->ipAdd, "/etc/")).exists()
            QDir(QString("%1%2%3").arg("\\\\", this->ipAdd, "/log/")).exists())
#elif linux
    if(QDir("/usr/local/ubecontrol/").exists() && QDir("/usr/local/etc/").exists() && QDir("/Storage/log/").exists())
#endif
    {
        if(!configFile->exists())
            _return.append(0);
        else
            _return.append(1);
        if(!statusFile->exists())
            _return.append(0);
        else
            _return.append(1);
        if(!videoChannelFile->exists())
            _return.append(0);
        else
            _return.append(1);
        if(!uberecorderFile->exists())
            _return.append(0);
        else
            _return.append(1);
        if(!logFile->exists())
            _return.append(0);
        else
            _return.append(1);
    }
    else _return.append(-1);
    return _return;
}

serverType filecontrol::readConfigFile()
{
    QString projectName;
    serverType _server;
    QList< formatType> _formatList;
    QList< streamtype> _streamList;
    configFile->open(QFile::ReadOnly);
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode streamChild;
    QDomNode formatChild;
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    streamChild = root.firstChild();
    while(!streamChild.isNull())
    {
        if(streamChild.toElement().tagName() == "stream")
        {
            streamtype _stream;

            projectName = streamChild.toElement().attribute("project_name");
            _stream.streamID = streamChild.toElement().attribute("stream_id").toInt();
            _stream.channel = streamChild.toElement().attribute("channel_num").toInt();
            _stream.aspect = streamChild.toElement().attribute("aspect");
            _stream.audioTrack = streamChild.toElement().attribute("count_audio_track").toInt();
            _stream.split = streamChild.toElement().attribute("split_minutes").toInt();
            _stream.thumb = streamChild.toElement().attribute("thumbnail").toInt();
            _stream.thumPPS = streamChild.toElement().attribute("thumbnail_pic_per_sec").toInt();
            _stream.enable = streamChild.toElement().attribute("enbale").toInt();
            _stream.restart = streamChild.toElement().attribute("restart").toInt();
            if(!streamChild.toElement().attribute("project_nr").isNull() && !streamChild.toElement().attribute("project_nr").isEmpty() )
            {
                _stream.projectNr = streamChild.toElement().attribute("project_nr").toInt();
            }
            formatChild = streamChild.firstChild();
            while(!formatChild.isNull())
            {
                if(formatChild.toElement().tagName() == "format")
                {
                    formatType _format;
                    _format.codec = formatChild.toElement().attribute("resolution");
                    _format.tapeName = formatChild.toElement().attribute("default_tapename");
                    _format.fileName = formatChild.toElement().attribute("default_filename");
                    _format.creatingPath = formatChild.toElement().attribute("creating_path");
                    _format.archivPath = formatChild.toElement().attribute("archiv_path");
                    _format.archivResultPath = formatChild.toElement().attribute("archiv_result_path");
                    _format.scale = formatChild.toElement().attribute("scale");
                    _format.videoBit = formatChild.toElement().attribute("video_bitrate").toInt();
                    _format.audioBit = formatChild.toElement().attribute("audio_bitrate").toInt();
                    _format.timeOverlay = formatChild.toElement().attribute("timecode_coverlay").toInt();
                    _formatList.append(_format);
                }
                formatChild = formatChild.nextSibling();
            }
            _stream.formatList = _formatList;
            _formatList.clear();

            _streamList.append(_stream);

        }
        streamChild = streamChild.nextSibling();
    }
    _server.projectName = projectName;
    _server.ipAdd = ipAdd;
    _server.serverName = serverName;
    _server.streamList = _streamList;
    _server.cardList = this->readVideoChannelFile();
    _server.IOCapture = this->getStatus();
    _streamList.clear();

    configFile->close();
    return _server;
}

QList<messageType> filecontrol::readLogFile(QString ipAdd, QList<messageType> messageList, int pos)
{
    QList<messageType> _list = messageList;
    QFile* logFile = new QFile();
#ifdef _WIN32
    logFile->setFileName(QString("%1%2%3").arg("\\\\", ipAdd, "/log/dvs_sdi.log"));
#elif linux
    logFile->setFileName("/Storage/log/dvs_sdi.log");
#endif
    //////////////is this part nessary?
    if(pos == 0)
    {
        logFile->close();
    }
    //////////////////////////////////
    if(logPos > logFile->size())
    {
        logPos = 0;
    }

    logFile->open(QFile::ReadOnly);
    logFile->seek(logPos);
    QString line;

    while(!logFile->atEnd())
    {
        line = logFile->readLine();
        if(line.left(2).toInt() > 0 && line.left(2).toInt() < 31)
        {
            messageType message(line);
            _list.append(message);
        }
    }
    logPos = logFile->pos();
    logFile->close();
    return _list;
}

QString filecontrol::readUberecorderFile()
{
    uberecorderFile->open(QFile::ReadOnly);
    QString line;
    while(!uberecorderFile->atEnd())
    {
        line = uberecorderFile->readLine();
        if(line.contains("name"))
        {
            serverName = line.remove("name = \"");
            serverName = serverName.remove("\"");
        }
    }
    uberecorderFile->close();
    qDebug()<<serverName;
    return serverName;
}

QList< cardtype> filecontrol::readVideoChannelFile()
{
    QList< cardtype> cardList;
    videoChannelFile->open(QFile::ReadOnly);
    QString line;
    while(!videoChannelFile->atEnd())
    {
        line = videoChannelFile->readLine();
        if(!line.contains("#"))
        {
            cardtype card;
            QList< int> channelList;
            QString _index = line.split(";").at(0);
            _index = _index.remove("videocard");
            card.index = _index.toInt();
            card.name = line.split(";").at(2);
            for(int i = 0; i < line.split(";").at(1).split(" ").count(); i++)
            {
                channelList.append(line.split(";").at(1).split(" ").at(i).toInt());
            }
            card.channelList = channelList;
            channelList.clear();
            cardList.append(card);
        }
    }
    videoChannelFile->close();
    return cardList;

}

QList< cardtype> filecontrol::readVideoChannelFile(QString ipAdd)
{
    QList< cardtype> cardList;
    QFile* File = new QFile();
#ifdef _WIN32
    File->setFileName(QString("%1%2%3").arg("\\\\", this->ipAdd, "/etc/vc_new.conf"));
#elif linux
    File->setFileName("/usr/local/etc/vc_new.conf");
#endif
    if(File->isOpen())
        File->close();
    File->open(QFile::ReadOnly);
    QString line;
    while(!File->atEnd())
    {
        line = File->readLine();
        if(!line.contains("#"))
        {
            cardtype card;
            QList< int> channelList;
            QString _index = line.split(";").at(0);
            _index = _index.remove("videocard");
            card.index = _index.toInt();
            card.name = line.split(";").at(2);
            for(int i = 0; i < line.split(";").at(1).split(" ").count(); i++)
            {
                channelList.append(line.split(";").at(1).split(" ").at(i).toInt());
            }
            card.channelList = channelList;
            channelList.clear();
            cardList.append(card);
        }
    }
    File->close();
    return cardList;

}

int filecontrol::iniConfigFile()
{
    this->readUberecorderFile();
    configFile->open(QFile::WriteOnly);
    QString text;
    text.append("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");
    text.append("<capture>\n");
    text.append("<version date_update=\"2013-08-23 12:22:00\" /\n>");
    text.append(QString("<server id=\"%1\" name=\"%2\" ip=\"127.0.0.1\" />").arg(serverID, serverName));
    text.append(QString("</capture>"));
    QTextStream out(configFile);
    out<<text;
    configFile->close();
    return 0;
}

int filecontrol::iniVideoChannelFile()
{
    cardtype card;
    card.index = 0;
    card.channelList.append(1);
    card.channelList.append(2);
    card.name = "videocard0";
    QList< cardtype> cardList;
    cardList.append(card);
    this->writeVideoChannelFile(cardList);
    return 0;
}

int filecontrol::writeVideoChannelFile(QList< cardtype> cardList)
{
    if(videoChannelFile->open(QFile::WriteOnly))
    {
        QTextStream out(configFile);
        out<<";this file defined the videocard ID of channels\n"<<
             ";\n"<<";videoCard channelNo\n";
        for(int i = 0; i < cardList.count();i++)
        {
            out<<"videocard"<<cardList.at(i).index<<";";
            for(int j = 0; j < cardList.at(i).channelList.count(); j++)
            {
                out<<cardList.at(i).channelList.at(i)<<" ";
            }
            out<<cardList.at(i).name<<"\n";
        }
        videoChannelFile->close();
        return 1;
    }
    else
        return 0;
}

int filecontrol::setOrderFile(int start)
{
    QString text;
    text = "<?xml version='1.0' encoding='uft-8'?>\n";
    text.append("<order\n>");
    if(start == 1)
    {
        text.append("<Start>all</Start>\n");
    }
    else
    {
        text.append("<Stop>all</Stop>\n");
    }
    text.append("</order>\n");
    orderFile->open(QFile::WriteOnly);
    QTextStream out(orderFile);
    out<<text;
    orderFile->close();
    return 0;
}

int filecontrol::getStatus()
{
    int isCapture = 0;
    qDebug()<<statusFile->fileName();
    statusFile->open(QFile::ReadOnly);
    //else
    {

        int _find = 0;
        QString errorStr;
        int errorLine;
        int errorColumn;
        QDomDocument doc;
        QDomElement root;
        QDomNode serverChild;
        QDomNode streamChild;
        doc.setContent(statusFile, false, &errorStr, &errorLine, &errorColumn);
        root = doc.documentElement();
        serverChild = root.firstChild();
        while(!serverChild.isNull() && !_find)
        {
            if(serverChild.toElement().tagName() == "server")
            {
                streamChild = serverChild.firstChild();
                while(!streamChild.isNull() && !_find)
                {
                    if(streamChild.toElement().tagName() == "stream"){
                        if(streamChild.toElement().attribute("status") == "stopped")
                        {
                            isCapture = 0;
                        }
                        else
                        {
                            isCapture = 1;
                        }
                    }
                    streamChild = streamChild.nextSibling();
                }
            }
            serverChild = serverChild.nextSibling();
        }
    }

    statusFile->close();
    return isCapture;
}

int filecontrol::writeFormattoXML(serverType _server, streamtype _stream, formatType _format)
{
    if(configFile->isOpen())
    {
        configFile->close();
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    configFile->open(QFile::ReadOnly);
    {
        bool _streamfind = false;
        QDomNode child;
        QDomElement newChild;
        doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
        root = doc.documentElement();
        child = root.firstChild();
        while(!child.isNull() && !_streamfind)
        {
            if(child.toElement().tagName() == "stream")
            {
                if(child.toElement().attribute("stream_id").toInt() == _stream.streamID
                        && child.toElement().attribute("channel_num").toInt() == _stream.channel)
                {
                    _streamfind = true;
                    newChild = doc.createElement("format");
                    newChild.toElement().setAttribute("archiv_path", _format.archivPath);
                    newChild.toElement().setAttribute("archiv_result_path", _format.archivResultPath);
                    newChild.toElement().setAttribute("resolution", _format.codec);
                    newChild.toElement().setAttribute("creating_path", _format.creatingPath);
                    newChild.toElement().setAttribute("default_filename", _format.fileName);
                    newChild.toElement().setAttribute("default_tapename", _format.tapeName);
                    newChild.toElement().setAttribute("timecode_overlay", _format.timeOverlay);
                    newChild.toElement().setAttribute("enable", _format.enable);
                    newChild.toElement().setAttribute("restart", _format.restart);
                    if(_format.codec.compare("SD_MPEG4BP_AAC_MOV") == 0
                            || _format.codec.compare("SD_MPEG4MP_AAC_MOV") == 0)
                    {
                        newChild.toElement().setAttribute("video_bitrate", _format.videoBit);
                        newChild.toElement().setAttribute("scale", _format.scale);
                        newChild.toElement().setAttribute("audio_bitrate", _format.audioBit);
                        newChild.toElement().setAttribute("name", _server.projectName);
                    }
                    child.appendChild(newChild);
                }
            }
            child = child.nextSibling();
        }
        if(!_streamfind)
        {
            newChild = doc.createElement("stream");
            newChild.toElement().setAttribute("aspect", _stream.aspect);
            newChild.toElement().setAttribute("count_audio_track", _stream.audioTrack);
            newChild.toElement().setAttribute("channel_num", _stream.channel);
            newChild.toElement().setAttribute("enable", _stream.enable);
            if(_stream.projectNr == -1)
                newChild.toElement().setAttribute("project_nr","");
            else
                newChild.toElement().setAttribute("project_nr", _stream.projectNr);
            newChild.toElement().setAttribute("restart", _stream.restart);
            newChild.toElement().setAttribute("split_minutes", _stream.split);
            newChild.toElement().setAttribute("stream_id", _stream.streamID);
            newChild.toElement().setAttribute("thumbnail", _stream.thumb);
            newChild.toElement().setAttribute("thumbnail_pic_per_sec", _stream.thumPPS);
            QDomElement subChild = doc.createElement("format");
            subChild.toElement().setAttribute("archiv_path", _format.archivPath);
            subChild.toElement().setAttribute("archiv_result_path", _format.archivResultPath);
            subChild.toElement().setAttribute("resolution", _format.codec);
            subChild.toElement().setAttribute("creating_path", _format.creatingPath);
            subChild.toElement().setAttribute("default_filename", _format.fileName);
            subChild.toElement().setAttribute("default_tapename", _format.tapeName);
            subChild.toElement().setAttribute("timecode_overlay", _format.timeOverlay);
            subChild.toElement().setAttribute("enable", _format.enable);
            subChild.toElement().setAttribute("restart", _format.restart);
            if(_format.codec.compare("SD_MPEG4BP_AAC_MOV") == 0
                    || _format.codec.compare("SD_MPEG4MP_AAC_MOV") == 0)
            {
                subChild.toElement().setAttribute("video_bitrate", _format.videoBit);
                subChild.toElement().setAttribute("scale", _format.scale);
                subChild.toElement().setAttribute("audio_bitrate", _format.audioBit);
                subChild.toElement().setAttribute("name", _server.projectName);
            }
            newChild.appendChild(subChild);
            root.appendChild(newChild);
        }
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    QTextStream out(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();

    return 0;
}

int filecontrol::removeFormat(QString ipAdd, QString channel, QString streamID, QString format)
{
    if(configFile->isOpen())
    {
        configFile->close();
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode streamChild;
    configFile->open(QFile::ReadOnly);
    int _find = 0;
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    streamChild = root.firstChild();
    while(!streamChild.isNull() && !_find)
    {
        if(streamChild.toElement().tagName() == "stream")
        {
            if(streamChild.toElement().attribute("channel_num") == channel && streamChild.toElement().attribute("stream_id") == streamID)
            {
                QDomNode formatChild;
                formatChild = streamChild.firstChild();
                while(!formatChild.isNull() && !_find)
                {
                    if(formatChild.toElement().attribute("resolution") == format)
                    {
                        _find = 1;
                        streamChild.removeChild(formatChild);
                    }
                    formatChild = formatChild.nextSibling();
                }
                if(!streamChild.hasChildNodes())
                {
                    root.removeChild(streamChild);
                }
            }
        }
        streamChild = streamChild.nextSibling();
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    QTextStream out(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();
    return _find;
}

int filecontrol::removeStream(QString ipAdd, QString channel, QString streamID)
{
    if(configFile->isOpen())
    {
        configFile->close();
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode streamChild;
    configFile->open(QFile::ReadOnly);
    int _find = 0;
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    streamChild = root.firstChild();
    while(!streamChild.isNull() && !_find)
    {
        if(streamChild.toElement().tagName() == "stream")
        {
            if(streamChild.toElement().attribute("channel_num") == channel && streamChild.toElement().attribute("stream_id") == streamID)
            {
                _find = 1;
                root.removeChild(streamChild);
            }
        }
        streamChild = streamChild.nextSibling();
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    QTextStream out(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();
    return _find;
}
int filecontrol::removeChannel(QString ipAdd, QString channel)
{
    if(configFile->isOpen())
    {
        configFile->close();
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode streamChild;
    configFile->open(QFile::ReadOnly);
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    streamChild = root.firstChild();
    while(!streamChild.isNull())
    {
        if(streamChild.toElement().tagName() == "stream")
        {
            if(streamChild.toElement().attribute("channel_num") == channel)
            {
                root.removeChild(streamChild);
            }
        }
        streamChild = streamChild.nextSibling();
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    QTextStream out(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();
    return 0;
}

int filecontrol::setServerName(QString serverName)
{
    if(uberecorderFile->isOpen())
    {
        uberecorderFile->close();
    }
    uberecorderFile->open(QFile::ReadOnly);
    QStringList LineList;
    QString line;
    while(!uberecorderFile->atEnd())
    {
        line = uberecorderFile->readLine();
        if(line.contains("name = "))
        {
            line = QString("name = \"%1\"").arg(serverName);
        }
        LineList.append(line);
    }
    uberecorderFile->close();
    uberecorderFile->open(QFile::WriteOnly);
    QTextStream out(uberecorderFile);
    for(int i = 0; i < LineList.count(); i++)
    {
        out<<LineList.at(i);
    }
    uberecorderFile->close();
    out.reset();
    if(configFile->isOpen())
    {
        configFile->close();
    }

    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode serverChild;
    configFile->open(QFile::ReadOnly);
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    serverChild = root.firstChild();
    while(!serverChild.isNull())
    {
        if(serverChild.toElement().tagName() == "server")
        {
            serverChild.toElement().setAttribute("name", serverName);
        }
        serverChild = serverChild.nextSibling();
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    out.setDevice(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();

    return 0;
}

int filecontrol::setProjectName(QString projectName)
{
    if(configFile->isOpen())
    {
        configFile->close();
    }

    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode streamChild;
    configFile->open(QFile::ReadOnly);
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    streamChild = root.firstChild();
    while(!streamChild.isNull())
    {
        if(streamChild.toElement().tagName() == "stream")
        {
            streamChild.toElement().setAttribute("project_name", projectName);
        }
        streamChild = streamChild.nextSibling();
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    QTextStream out(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();

    return 0;
}

int filecontrol::streamEdittoXML(streamtype preStream, streamtype currentStream)
{
    if(configFile->isOpen())
    {
        configFile->close();
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode streamChild;
    configFile->open(QFile::ReadOnly);
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    streamChild = root.firstChild();
    int _find = 0;
    while(!streamChild.isNull() && !_find)
    {
        if(streamChild.toElement().tagName() == "stream"
            && streamChild.toElement().attribute("stream_id").toInt() == preStream.streamID
            && streamChild.toElement().attribute("channel_num").toInt() == preStream.channel)
        {
            _find = 1;
            streamChild.toElement().setAttribute("aspect", currentStream.aspect);
            streamChild.toElement().setAttribute("count_audio_track", currentStream.audioTrack);
            streamChild.toElement().setAttribute("enable", currentStream.enable);
            if(currentStream.projectNr != -1)
                streamChild.toElement().setAttribute("project_nr", currentStream.projectNr);
            streamChild.toElement().setAttribute("restart", currentStream.restart);
            streamChild.toElement().setAttribute("split_minutes", currentStream.split);
            streamChild.toElement().setAttribute("thumbnail", currentStream.thumb);
            streamChild.toElement().setAttribute("thumbnail_pic_per_sec",currentStream.thumPPS);
            if(preStream.streamID != currentStream.streamID)
            {
                streamChild.toElement().setAttribute("stream_id", currentStream.streamID);
            }
            if(preStream.channel != currentStream.channel)
            {
                streamChild.toElement().setAttribute("channel_num", currentStream.channel);
            }
        }
        streamChild = streamChild.nextSibling();
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    QTextStream out(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();
    return 1;
}

int filecontrol::formatEdittoXML(streamtype currentStream, formatType preFormat, formatType currentFormat)
{
    int streamID = currentStream.streamID;
    int channel = currentStream.channel;
    if(configFile->isOpen())
    {
        configFile->close();
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    QDomElement root;
    QDomNode streamChild;
    configFile->open(QFile::ReadOnly);
    doc.setContent(configFile, false, &errorStr, &errorLine, &errorColumn);
    root = doc.documentElement();
    streamChild = root.firstChild();
    int _find = 0;
    while(!streamChild.isNull() && !_find)
    {
        if(streamChild.toElement().attribute("stream_id").toInt() == streamID && streamChild.toElement().attribute("channel_num").toInt() == channel)
        {
            QDomNode formatChild;
            formatChild = streamChild.firstChild();
            while(!formatChild.isNull() && !_find)
            {
                if(formatChild.toElement().attribute("resolution") == preFormat.codec)
                {
                    _find = 1;
                    formatChild.toElement().setAttribute("archiv_path", currentFormat.archivPath);
                    formatChild.toElement().setAttribute("archiv_result_path", currentFormat.archivResultPath);
                    formatChild.toElement().setAttribute("creating_path", currentFormat.creatingPath);
                    formatChild.toElement().setAttribute("default_filename", currentFormat.fileName);
                    formatChild.toElement().setAttribute("default_tapename", currentFormat.tapeName);
                    formatChild.toElement().setAttribute("timecode_overlay", currentFormat.timeOverlay);
                    formatChild.toElement().setAttribute("enable", currentFormat.enable);
                    formatChild.toElement().setAttribute("restart", currentFormat.restart);
                    if(currentFormat.codec.compare("SD_MPEG4BP_AAC_MOV") == 0
                            || currentFormat.codec.compare("SD_MPEG4MP_AAC_MOV") == 0)
                    {
                        formatChild.toElement().setAttribute("video_bitrate", currentFormat.videoBit);
                        formatChild.toElement().setAttribute("scale", currentFormat.scale);
                        formatChild.toElement().setAttribute("audio_bitrate", currentFormat.audioBit);
                    }

                    formatChild.toElement().setAttribute("resolution", currentFormat.codec);
                }
                formatChild = formatChild.nextSibling();
            }
        }
        streamChild = streamChild.nextSibling();
    }
    configFile->close();
    configFile->open(QFile::WriteOnly);
    QTextStream out(configFile);
    out.setCodec("UTF-8");
    doc.save(out, 4);
    doc.clear();
    configFile->close();
    return 1;
}

QString filecontrol::getVideoCard(QList<cardtype> cardList, int channel)
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
