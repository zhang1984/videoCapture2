#ifndef ERRORWIDGET_H
#define ERRORWIDGET_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QTreeWidget>
#include <QHeaderView>
#include <config/servertype.h>
#include <config/messagetype.h>
#include <config/filecontrol.h>
#include <GUI/ipelement.h>
#include <GUI/Dialog/errormessages.h>
#include <thread/messageupdate.h>
#include <QTimer>
#include <QThread>
#include <QtCore>

/*
class formatElement
{
public:
    formatElement();
    QString ipAdd;
    int streamID;
    QString codecName;
    int errorCount;
    int goodCount;
    int warningCount;
    int syncCount;
};

class streamElement
{
public:
    streamElement();
    QString ipAdd;
    int streamID;
    QList< formatElement> formatList;
    int errorCount;
    int goodCount;
    int warningCount;
    int syncCount;
};

class channelElement
{
public:
    channelElement();
    int channelID;
    QList<messageType> cMessageList;
};

class cardElement
{
public:
    cardElement();
    QString videoCard;
    QList<channelElement> channelList;
    QList<messageType> vMessageList;
};

class ipElement
{
public:
    ipElement();
    QString ipAdd;
    QList< cardElement> cardList;
    QList<messageType> iMessageList;
};*/

class errorwidget : public QWidget
{
    Q_OBJECT
public:
    explicit errorwidget(QWidget *parent = 0);

    QList<ipElement> elementList;
    QTreeWidget* errorWidget;
    QList<qint64> logPosList;
    QTimer upDateTimer;
    QThread _upDateThread;
    messageUpdate _messUpdate;

    errormessages* message;

    void CreateTreeWidget();
    QTreeWidgetItem* setServerType(serverType _server);
    void addTreeItem(serverType _server);
    void addTreeItem(QString ipAdd, QString cardName, int channel, int stream);

    int removeServer(QString ipAdd);

    void updateElements(QString ipAdd);
    void updateElements();

    QList<int> getMessageListStatic(QList<messageType>);

signals:

public slots:
    void infoDialogShow(QTreeWidgetItem*, int);
    void updateTable();
};

#endif // ERRORWIDGET_H
