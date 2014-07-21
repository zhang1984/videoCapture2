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
    \brief
    \param logPos : the current read position of the dvs_sdi.log
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
    \brief read the uberecorder file, get the information about the server name
    */
    QString readUberecorderFile();

    /**
    \brief remove the format, if succeed, return 1, else return 0
    \param ipAdd : ip address
    \param channel : channel number
    \param streamID : stream id number
    \param format : format name
    */
    int removeFormat(QString ipAdd, QString channel, QString streamID, QString format);

    /**
    \brief remove the stream, if removed, return 1, else return 0
    \param ipAdd : ip address
    \param channel : channel number
    \param streamID : stream id number
    */
    int removeStream(QString ipAdd, QString channel, QString streamID);

    /**
    \brief remove the channel, if removed, return 1, else return 0
    \param ipAdd : ip address
    \param channel : channel number
    */
    int removeChannel(QString ipAdd, QString channel);

    /**
    \brief write the video channel file, if succeed, return 1, else return 0
    \param cardType : the list of cardtype
    */
    int writeVideoChannelFile(QList< cardtype> cardTypeList);

    /**
    \brief write the format to config.xml, if succeed, return 1, else return 0
    \param _server : the serverType of the server
    \param _stream : the streamtype of the stream
    \param _format : the formatType for the format
    */
    int writeFormattoXML(serverType _server, streamtype _stream, formatType _format);

    /**
    \brief change the stream option in config.xml, if succeed, return 1, else return 0
    \param preStream : the previous stream information
    \param currentStream : the current stream information
    */
    int streamEdittoXML(streamtype preStream, streamtype currentStream);

    /**
    \brief change the format option in config.xml, if succeed, return 1, else return 0
    \param currentStream : the stream information
    \param preFormat : the previous format information
    \param currentFormat : the current format information
    */
    int formatEdittoXML(streamtype currentStream, formatType preFormat, formatType currentFormat);

    /**
    \brief read the video channel file, and return the as the list of cardtype
    */
    QList< cardtype> readVideoChannelFile();

    /**
    \brief read the video channel file, and return the as the list of cardtype
    \param ipAdd : ip address
    */
    QList< cardtype> readVideoChannelFile(QString ipAdd);

    /**
    \brief set the order.xml in the server, start or stop the server, return 1 succeed, else return 0
    \param start : start / stop the capture, 1/0
    */
    int setOrderFile(int start);

    /**
    \brief set the server name in the uberecorder file, if succeed, return 1, else return 0
    \param serverName : the name of the server
    */
    int setServerName(QString serverName);

    /**
    \brief set the project name, if succeed, return 1, else return 0
    \param projectName : the name of the project
    */
    int setProjectName(QString projectName);
    /**
    \brief get the video card name of the channel
    \param cardList : the list of cardtype
    \param channel : the id of the channel
    */
    QString getVideoCard(QList<cardtype> cardList, int channel);
    /**
    \brief get the current time information from the status.xml, saved as a tuple, include current TC and split
    \param stream : the stream of the capture
    \param channel : the channel id
    \param resolution : the resolution name of the format
    */
    std::tuple<QTime, int> getCurrentTime(QString stream, QString channel, QString resolution);
};

#endif // FILECONTROL_H
