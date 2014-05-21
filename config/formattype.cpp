#include "formattype.h"

formatType::formatType(int timeOverlay, int restart, int enable)
{
    this->timeOverlay = timeOverlay;
    this->restart = restart;
    this->enable = enable;
}

formatType::formatType(QString codec, QString tapeName, QString fileName, QString creatingPath,
                       QString archivPath, QString archivResultPath, QString scale, int video, int audio, int timeOverlay, int restart, int enable)
{
    this->codec = codec;
    this->tapeName = tapeName;
    this->fileName = fileName;
    this->creatingPath = creatingPath;
    this->archivPath = archivPath;
    this->archivResultPath = archivResultPath;
    this->scale = scale;
    this->videoBit = video;
    this->audioBit = audio;
    this->timeOverlay = timeOverlay;
    this->enable = enable;
    this->restart = restart;
}
