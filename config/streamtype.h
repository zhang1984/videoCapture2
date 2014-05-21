#ifndef STREAMTYPE_H
#define STREAMTYPE_H

#include <QString>
#include <config/formattype.h>

class streamtype
{
public:
    streamtype(int enable = 1, int restart = 0, int projectNr = -1);
    streamtype(int streamID, int channel, int audioTrack, QString aspect, int split,
                        int thumb, int thumPPS, int enable = 1, int restart = 0, int projectNr = -1);

    int streamID;
    int channel;
    int audioTrack;
    QString aspect;
    int split;
    int thumb;
    int thumPPS;
    int enable;
    int restart;
    int projectNr;
    QList< formatType> formatList;
};

#endif // STREAMTYPE_H
