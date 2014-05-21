#ifndef FORMATTYPE_H
#define FORMATTYPE_H

#include <QString>
#include <QList>

class formatType
{
public:

    explicit formatType(QString codec, QString tapeName, QString fileName, QString creatingPath,
                        QString archivPath, QString archivResultPath, QString scale, int video, int audio, int timeOverlay = 0, int restart = 0, int enable = 1);
    formatType(int timeOverlay = 0, int restart = 0, int enable = 1);
    QString codec;
    QString tapeName;
    QString fileName;
    QString creatingPath;
    QString archivPath;
    QString archivResultPath;
    QString scale;
    int videoBit;
    int audioBit;
    int timeOverlay;
    int enable;
    int restart;

};

#endif // FORMATTYPE_H
