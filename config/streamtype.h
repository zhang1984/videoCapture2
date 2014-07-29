#ifndef STREAMTYPE_H
#define STREAMTYPE_H

#include <QString>
#include <config/formattype.h>
/**
\brief
define the format type as config.xml
*/
class streamtype
{
public:
    /**
    \brief
    initial the streamtype with predefined parameters
    */
    streamtype(int enable = 1, int restart = 0, int projectNr = -1);
    /**
    \brief initial the streamtype with parameters
    */
    streamtype(int streamID, int channel, int audioTrack, QString aspect, int split,
                        int thumb, int thumPPS, int enable = 1, int restart = 0, int projectNr = -1);

    /**
    \brief
    \param streamID : stream_id
    */
    int streamID;
    /**
    \brief
    \param channel : channel_num
    */
    int channel;
    /**
    \brief
    \param audioTrack : count_audio_track
    */
    int audioTrack;
    /**
    \brief
    \param aspect : aspect
    */
    QString aspect;
    /**
    \brief
    \param split : split_minutes
    */
    int split;
    /**
    \brief
    \param thumb : thumbnail
    */
    int thumb;
    /**
    \brief
    \param thumPPS : thumbnail_pic_per_sec
    */
    int thumPPS;
    /**
    \brief
    \param enable : enbale
    */
    int enable;
    /**
    \brief
    \param restart : restart
    */
    int restart;
    /**
    \brief
    \param projectNr : project_nr
    */
    int projectNr;
    /**
    \brief
    \param formatList : the list of formats, which includes all the formatType under the stream
    */
    QList< formatType> formatList;
};

#endif // STREAMTYPE_H
