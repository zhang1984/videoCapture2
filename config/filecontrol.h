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
class filecontrol
{
public:
    filecontrol();
    filecontrol(QString ipAdd);

    QString ipAdd;
    QFile* configFile;
    QFile* statusFile;
    QFile* logFile;
    QFile* uberecorderFile;
    QFile* videoChannelFile;
    QFile* orderFile;
    QString projectName;
    QString serverName;
    QString serverID;
    qint64 logPos;


    int iniConfigFile();
    int iniVideoChannelFile();
    int setFile(QString ipAAd, int noDialog = 0);
    QList< int> isServer();
    serverType readConfigFile();
    int getStatus();
    QList<messageType> readLogFile(QString ipAdd, QList<messageType> messageList, int pos = 0);
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
};

#endif // FILECONTROL_H
