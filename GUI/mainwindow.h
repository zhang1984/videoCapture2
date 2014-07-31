#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <GUI/menubar.h>
#include <GUI/treewidget.h>
#include <GUI/centralwidget.h>
#include <GUI/errorwidget.h>
#include <GUI/Dialog/openserverdialog.h>
#include <GUI/Dialog/adddialog.h>
#include <GUI/Dialog/servereditdialog.h>
#include <GUI/Dialog/streameditdialog.h>
#include <GUI/Dialog/formateditdialog.h>
#include <config/servertype.h>
#include <config/filecontrol.h>
#include <thread/messageupdate.h>
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QDebug>
/**
\brief define the main window of the GUI
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
    \brief initial the main window
    */
    MainWindow(QWidget *parent = 0);
    /**
    \brief mem free of main window
    */
    ~MainWindow();
    /**
    \brief
    \param menuBar : the menu bar of the GUI
    */
    menubar* menuBar;
    /**
    \brief
    \param treeWidget : the widget in the left size of the gui, including the tree widget of the server
    */
    treewidget* treeWidget;
    /**
    \brief
    \param centralWidget : the central widget shows the options of item
    */
    centralwidget* centralWidget;
    /**
    \brief
    \param errorWidget : the widget shows the information of the servers from dvs_sdi.log
    */
    errorwidget* errorWidget;
    /**
    \brief
    \param _fctrl : the file control object
    */
    filecontrol* _fctrl;

    openServerDialog *_openServerDialog;
    addDialog* _addDialog;
    serverEditDialog* _serverEditDialog;
    streameditdialog* _streamEditDialog;
    formateditdialog* _formatEditDialog;
    /**
    \brief
    \param serverList : the list contains all the serverType
    */
    QList<serverType> serverList;

    /**
    \brief
    \param editIndex : the index records the serverindex streamindex and formatindex for edit.
    */
    QList<int> editIndex;
    /**
    \brief
    \param _copyFormat : save the formatType for copy
    */
    formatType _copyFormat;

    /////////////////////////Timer and QThread//////////////////
    //QTimer errorWidgetTimer;
    //QThread errorWidgetThread;
    /**
    \brief set the SIGNAL-SLOT connection
    */
    void setConnect();
    /**
    \brief add the new format to the server list and the treeWidget
    */
    int addFormatToServerList(serverType _server, streamtype _stream, formatType _format);
    /**
    \brief remove the format from the serverList and the treeWidget
    */
    int removeFormat(QString _server, QString _card, int channel, int stream, QString codec);
    /**
    \brief remove the stream and call the removeFormat() function
    */
    int removeStream(QString _server, QString _card, int channel, int stream);
    /**
    \brief remove the channel and call removeStream() function
    */
    int removeChannel(QString _server, QString _card, int channel);
    /**
    \brief remove the card and call the removeChannel() funktion
    */
    int removeCard(QString _server, QString _card);
    /**
    \brief remove the server and call the removeCard() funktion
    */
    int removeServer(QString _server);

signals:
    /**
    \brief SIGNAL, detect if the tree existed in the treewidget
    */
    void hasTree(bool);
    /**
    \brief SIGNAL, detect if the _copyFormat has the format
    */
    void hasCopy(int);

public Q_SLOTS:
    /**
    \brief Slot, to enable/disable the addAct
    */
    void setAddActEnabled(bool);
    /**
    \brief Slot, to set the buttons in treewidget enable/disable
    */
    void setTreeButtonsEnabled(bool);
    /**
    \brief Slot, to open the server files
    */
    void openServerSlot();
    /**
    \brief addAct slot, to popout an adddialog
    */
    void addActSlot();
    /**
    \brief serverEditAct slot, to popout a serverEditDialog
    */
    void serverEditActSlot();
    /**
    \brief stream edit Slot, to popout a streameditdialog
    */
    void streamEditActSlot();
    /**
    \brief format edit slot, to popout a formateditdialog
    */
    void formatEditActSlot();

    /**
    \brief the slot to add the server
    */
    void addServerSlot();
    /**
    \brief the slot to add the stream
    */
    void addStreamSlot();
    /**
    \brief the slot to remove the server, video card, channel, stream or format. depends on the focus position
    */
    void removeSlot();
    /**
    \brief refresh the setting, to reload the server
    */
    void reloadSlot();
    /**
    \brief the double click slot in treewidget
    */
    void treeItemDoubleClickedSlot();
    /**
    \brief the slot to change the server configuration
    */
    void serverEditChangedSlot();
    /**
    \brief the slot to change the stream configuration
    */
    void streamEditChangedSlot();
    /**
    \brief the slot to change the format configuration
    */
    void formatEditChangedSlot();
    /**
    \brief copy slot for format item
    */
    void copySlot();
    //void cutSlot();
    /**
    \brief paste slot for format item
    */
    void pasteSlot();
    /**
    \brief slot, to enbale the copy function
    */
    void setCopyEnabledSlot(QTreeWidgetItem*,QTreeWidgetItem*);
    /**
    \brief slot, to enable the paste function, if the _copyFormat is not empty
    */
    void setPasteEnabledSlot(int);
};

#endif // MAINWINDOW_H
