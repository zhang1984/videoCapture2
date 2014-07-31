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
/**
\brief define the message widget in GUI and shows the number of different types of the messages in the widget
*/
class errorwidget : public QWidget
{
    Q_OBJECT
public:
    /**
    \brief initial the errorwidget
    */
    explicit errorwidget(QWidget *parent = 0);
    /**
    \brief
    \param elementList : the list of the ipElement
    */
    QList<ipElement> elementList;
    /**
    \brief
    \param errorWidget : the tree widget of GUI
    */
    QTreeWidget* errorWidget;
    /**
    \brief
    \param logPosList : list of the position, which read the dvs_sdi.log file
    */
    QList<qint64> logPosList;
    /**
    \brief
    \param upDateTimer : the timer for update the message information
    */
    QTimer upDateTimer;
    /**
    \brief
    \param _upDateThread : the thread for update the message
    */
    QThread _upDateThread;
    /**
    \brief
    \param _messUpdate : the messageUpdate object in thread
    */
    messageUpdate _messUpdate;
    errormessages* message;

    void CreateTreeWidget();
    /**
    \brief return the QTreeWidgetItem with a server structure include all the sub item under the server
    */
    QTreeWidgetItem* setServerType(serverType _server);
    /**
    \brief add the server in the errorWidget
    */
    void addTreeItem(serverType _server);
    /**
    \brief add the stream into the errorWidget
    */
    void addTreeItem(QString ipAdd, QString cardName, int channel, int stream);
    /**
    \brief remove the server item in errorWidget
    */
    int removeServer(QString ipAdd);
    /**
    \brief update the message of a single server
    */
    void updateElements(QString ipAdd);
    /**
    \brief update the message of servers in the errorWidget
    */
    void updateElements();
    /**
    \brief count the numbers of different message tpye
    */
    QList<int> getMessageListStatic(QList<messageType>);

signals:

public slots:
    /**
    \brief popout the information errormessages dialog
    */
    void infoDialogShow(QTreeWidgetItem*, int);
    /**
    \brief read the dvs_sdi.log and update the number of the message types
    */
    void updateTable();
};

#endif // ERRORWIDGET_H
