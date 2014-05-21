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
class treewidget
{
public:
    treewidget();
    QTreeWidget* tWidget;
    QDockWidget* projectWidget;

    QWidget* buttonWidget;

    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* addButton;
    QPushButton* minusButton;
    QPushButton* refreshButton;

    void createtWidget();
    void createButtonWidget();

    QTreeWidgetItem* createTreeItem(serverType server);
    void addFormatItem(serverType _server, QString cardName, streamtype _stream, formatType _format, int i);
    void addServerItem(serverType server);

    int removeFormatItem(QString server, QString videocard, int channel, int stream, QString format);
    int removeStreamItem(QString server, QString videocard, int channel, int stream);
    int removeChannelItem(QString server, QString videocard, int channel);
    int removeCardItem(QString server, QString videocard);
    int removeServerItem(QString server);

    int reloadTree(QList<serverType> serverList);

    QStringList getCurrentItemInfo();

signals:
    void hasTree(bool);
public Q_SLOTS:
    void setButtonsEnabled(bool);
};

#endif // TREEWIDGET_H
