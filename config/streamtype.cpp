#include "streamtype.h"

streamtype::streamtype(int enable, int restart, int projectNr)
{
    this->enable = enable;
    this->restart = restart;
    this->projectNr = projectNr;
}


streamtype::streamtype(int streamID, int channel, int audioTrack, QString aspect, int split,
                       int thumb, int thumPPS, int enable, int restart, int projectNr)
{
    this->streamID = streamID;
    this->channel = channel;
    this->audioTrack = audioTrack;
    this->aspect = aspect;
    this->split = split;
    this->thumb = thumb;
    this->thumPPS = thumPPS;
    this->enable = enable;
    this->restart = restart;
    this->projectNr = projectNr;
}
