#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <QFile>
#include <QString>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <config/cardtype.h>
#include <config/servertype.h>
#include <config/messagetype.h>
#include <QDir>
#include <QDebug>
#include <QDomDocument>
#include <QTime>
#include <tuple>
/**
    \brief
    r/w the files in the server, get the information
*/
class filecontrol
{
public:
    /**
    \brief
    initial
    */
    filecontrol();
    /**
      \brief initial with the ip adress or host name
    */
    filecontrol(QString ipAdd);

    /**
    \brief
    \param ipAdd : the ip adress or host name
    */
    QString ipAdd;
    /**
    \brief
    \param configFile : the config.xml in the server with the path /usr/local/ubecontrol/config.xml
    */
    QFile* configFile;
    /**
    \brief
    \param statusFile : the status.xml in the server with the path /usr/local/ubecontrol/status.xml
    */
    QFile* statusFile;
    /**
    \brief
    \param logFile : the dvs_sdi.log in the server with the path /Storage/[project name]/dvs_sdi.log
    */
    QFile* logFile;
    /**
    \brief
    \param uberecorderFile : the uberecorder file in the server with the path /usr/local/etc/uberecorder.conf
    */
    QFile* uberecorderFile;
    /**
    \brief
    \param videoChannelFile : the video channel file in the server with the path /usr/local/etc/vc_new.conf save the information about the channel under each video card
    */
    QFile* videoChannelFile;
    /**
        \brief
        \param orderFile : the order File file in the server with the path /usr/local/ubecontrol/order.xml
        */
    QFile* orderFile;
    /**
      \brief
    \param projectName : the name of project
    */
    QString projectName;
    /**
    \brief
    \param serverName : the name of server
    */
    QString serverName;
    /**
    \brief
    \param serverID : the id number of server
    */
    QString serverID;
    /**
    \brief logPos : the current read position of the dvs_sdi.log
    */
    qint64 logPos;

    /**
    \brief initial the config file
    */
    int iniConfigFile();

    /**
    \brief initial the video channel file
    */
    int iniVideoChannelFile();
    /**
    \brief initial the files path
    \param ipAdd : ip address
    \param noDialog : with/without the dialog-GUI
    */
    int setFile(QString ipAdd, int noDialog = 0);

    /**
    \brief test, whether all the necessary files are existed in the server
    */
    QList< int> isServer();

    /**
    \brief read the config file, return the serverType
    */
    serverType readConfigFile();

    /**
    \brief read the status file, return whether the capture is started (1) or stopped (0)
    */
    int getStatus();

    /**
    \brief read the logFile, save a list of messageType, and change the logPos to the last position of log file
    \param ipAdd : the ip address
    \param messageList : the list of messageType
    \param pos : the begin position of the reader
    */
    QList<messageType> readLogFile(QString ipAdd, QList<messageType> messageList, int pos = 0);

    /**
    \brief
    */
    QString readUberecorderFile();
    int removeFormat(QString ipAdd, QString channel, QString streamID, QString format);
    int removeStream(QString ipAdd, QString channel, QString streamID);
    int removeChannel(QString ipAdd, QString channel);

    int writeVideoChannelFile(QList< cardtype>);
    int writeFormattoXML(serverType _server, streamtype _stream, formatType _format);

    int streamEdittoXML(streamtype preStream, streamtype currentStream);
    int formatEdittoXML(streamtype currentStream, formatType preFormat, formatType currentFormat);

    QList< cardtype> readVideoChannelFile();
    QList< cardtype> readVideoChannelFile(QString ipAdd);
    int setOrderFile(int start);

    int setServerName(QString serverName);
    int setProjectName(QString projectName);
    QString getVideoCard(QList<cardtype> cardList, int channel);

    std::tuple<QTime, int> getCurrentTime(QString stream, QString channel, QString resolution);
};

#endif // FILECONTROL_H
