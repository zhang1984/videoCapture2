#ifndef FORMATTYPE_H
#define FORMATTYPE_H

#include <QString>
#include <QList>

/**
\brief
define the format type as config.xml
*/
class formatType
{
public:
    /**
    \brief
    initial the formatType
    */
    explicit formatType(QString codec, QString tapeName, QString fileName, QString creatingPath,
                        QString archivPath, QString archivResultPath, QString scale, int video, int audio, int timeOverlay = 0, int restart = 0, int enable = 1);
    /**
    \brief
    initial the formatType
    */
    formatType(int timeOverlay = 0, int restart = 0, int enable = 1);
    /**
    \brief
    \param codec : resolution
    */
    QString codec;
    /**
    \brief
    \param tapeName : default_tapename
    */
    QString tapeName;
    /**
    \brief
    \param fileName : default_filename
    */
    QString fileName;
    /**
    \brief
    \param creatingPath : creating_path
    */
    QString creatingPath;
    /**
    \brief
    \param archivPath : archiv_path
    */
    QString archivPath;
    /**
    \brief
    \param archivResultPath : archiv_result_path
    */
    QString archivResultPath;
    /**
    \brief
    \param scale : scale
    */
    QString scale;
    /**
    \brief
    \param videoBit : video_bitrate
    */
    int videoBit;
    /**
    \brief
    \param audioBit : audio_bitrate
    */
    int audioBit;
    /**
    \brief
    \param timeOverlay : timeoverlay
    */
    int timeOverlay;
    /**
    \brief
    \param enable : enable
    */
    int enable;
    /**
    \brief
    \param restart : restart
    */
    int restart;

};

#endif // FORMATTYPE_H
