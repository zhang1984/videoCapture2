#ifndef SERVERTYPE_H
#define SERVERTYPE_H

#include <QWidget>
#include <config/cardtype.h>
#include <config/streamtype.h>
#include <QList>

class serverType
{
public:
    serverType();
    serverType(QString projectName, QString ipAdd, QString serverName);
    serverType(QString projectName, QString ipAdd, QString serverName, QList< streamtype> streamList, QList< cardtype> cardList);
    QString projectName;
    QString ipAdd;
    QString serverName;
    QList< streamtype> streamList;
    QList< cardtype> cardList;
    int IOCapture;
    QString getVideoCard(int channel);
};

#endif // SERVERTYPE_H
