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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    menubar* menuBar;
    treewidget* treeWidget;
    centralwidget* centralWidget;
    errorwidget* errorWidget;
    filecontrol* _fctrl;

    openServerDialog *_openServerDialog;
    addDialog* _addDialog;
    serverEditDialog* _serverEditDialog;
    streameditdialog* _streamEditDialog;
    formateditdialog* _formatEditDialog;

    QList<serverType> serverList;

    ///////the index records the serverindex streamindex and formatindex for edit./////
    QList<int> editIndex;

    formatType _copyFormat;

    /////////////////////////Timer and QThread//////////////////
    //QTimer errorWidgetTimer;
    //QThread errorWidgetThread;

    void setConnect();
    int addFormatToServerList(serverType _server, streamtype _stream, formatType _format);

    int removeFormat(QString _server, QString _card, int channel, int stream, QString codec);
    int removeStream(QString _server, QString _card, int channel, int stream);
    int removeChannel(QString _server, QString _card, int channel);
    int removeCard(QString _server, QString _card);
    int removeServer(QString _server);

signals:
    void hasTree(bool);
    void hasCopy(int);

public Q_SLOTS:
    void setAddActEnabled(bool);
    void setTreeButtonsEnabled(bool);
    void openServerSlot();
    void addActSlot();
    void serverEditActSlot();
    void streamEditActSlot();
    void formatEditActSlot();

    void addServerSlot();
    void addStreamSlot();
    void removeSlot();
    void reloadSlot();

    void treeItemDoubleClickedSlot();

    void serverEditChangedSlot();
    void streamEditChangedSlot();
    void formatEditChangedSlot();

    void copySlot();
    //void cutSlot();
    void pasteSlot();

    void setCopyEnabledSlot(QTreeWidgetItem*,QTreeWidgetItem*);
    void setPasteEnabledSlot(int);
};

#endif // MAINWINDOW_H
