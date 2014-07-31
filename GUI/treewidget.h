#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QDockWidget>
#include <QPushButton>
#include <QGridLayout>
#include <config/servertype.h>
#include <QList>
#include <QDebug>
#include <QObject>

/**
\brief define the treewidget as the server tree list widget
*/
class treewidget
{
public:
    /**
    \brief initial treewidget
    */
    treewidget();
    /**
    \brief
    \param tWidget : the tree widget to show the tree list
    */
    QTreeWidget* tWidget;
    /**
    \brief
    \param projectWidget : the container for the widget
    */
    QDockWidget* projectWidget;
    /**
    \brief
    \param buttonWidget : the sub container, for buttons
    */
    QWidget* buttonWidget;
    /**
    \brief
    \param startButton : start capture button for all server
    */
    QPushButton* startButton;
    /**
    \brief
    \param startButton : stop capture button for all server
    */
    QPushButton* stopButton;
    /**
    \brief
    \param addButton : the add button for add function
    */
    QPushButton* addButton;
    /**
    \brief
    \param minusButton : the remove button for remove function
    */
    QPushButton* minusButton;
    /**
    \brief
    \param refreshButton : the reload button for reload function
    */
    QPushButton* refreshButton;
    /**
    \brief create the tWidget
    */
    void createtWidget();
    /**
    \brief create the buttonWidget
    */
    void createButtonWidget();
    /**
    \brief create the treewidget
    */
    QTreeWidgetItem* createTreeItem(serverType server);
    /**
    \brief add the format item in tWidget
    */
    void addFormatItem(serverType _server, QString cardName, streamtype _stream, formatType _format, int i);
    /**
    \brief add the server item in tWidget
    */
    void addServerItem(serverType server);
    /**
    \brief remove the format item in tWidget
    */
    int removeFormatItem(QString server, QString videocard, int channel, int stream, QString format);
    /**
    \brief remove the stream item in tWidget
    */
    int removeStreamItem(QString server, QString videocard, int channel, int stream);
    /**
    \brief remove the channel item in tWidget
    */
    int removeChannelItem(QString server, QString videocard, int channel);
    /**
    \brief remove the card item in tWidget
    */
    int removeCardItem(QString server, QString videocard);
    /**
    \brief remove the server item in tWidget
    */
    int removeServerItem(QString server);
    /**
    \brief reload the tWidget
    */
    int reloadTree(QList<serverType> serverList);
    /**
    \brief get the configuration data of the current item
    */
    QStringList getCurrentItemInfo();

signals:
    /**
    \brief SIGNAL, if the the tWidget hat the items
    */
    void hasTree(bool);
public Q_SLOTS:
    /**
    \brief Slot, set the buttons in buttonWidget en/dis-able
    */
    void setButtonsEnabled(bool);
};

#endif // TREEWIDGET_H
