#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QDebug>

class messageType
{
    //Q_OBJECT
public:
    explicit messageType();
    messageType(int datum, QString time, QString device, QString message, int type);

    messageType(QString line);
    int datum;
    QString time;
    QString message;
    QString device;
    ///////////good = 1; Error = 2; Warning = 3; Sync = 4;
    int type;

    int getMessageType(QString message);

//signals:

//public slots:

};

#endif // MESSAGETYPE_H
