#include "messagetype.h"

messageType::messageType()
{
}

messageType::messageType(int datum, QString time, QString device, QString message, int type)
{
    this->datum = datum;
    this->time = time;
    this->device = device;
    this->message = message;
    this->type = type;
}

messageType::messageType(QString line)
{
    QStringList lineList = line.split(" ");
    if(lineList.at(0).toInt() > 0 && lineList.at(0).toInt() < 31)
    {
        datum = lineList.at(0).toInt();
        time = lineList.at(1);
        time = time.left(8);
        if(lineList.at(2).contains("card") || lineList.at(2).contains("chan") 
        //        || (lineList.at(2).contains("Primary") && (lineList.at(3).contains("capture"))) 
        //        || (lineList.at(2).contains("Secondary") && (lineList.at(3).contains("capture")))
                )
        {
            device = lineList.at(2) + " " + lineList.at(3);
            device = device.remove(":");
        }
        message = line.remove(lineList.at(0));
        message = message.remove(0, 1);
        QString t = message.split(" ").at(0);
        message = message.remove(t);
        message = message.remove(0, 1);
        if(!device.isEmpty())
        {
            QString device_s = device + ":";
            message = message.remove(device_s);
        }
        type = getMessageType(message);
    }
}

int messageType::getMessageType(QString message)
{
    int att = 0;
    if(message.contains("device present", Qt::CaseSensitive)
            || message.contains("second channel", Qt::CaseSensitive)
            || message.contains("Primary capture", Qt::CaseSensitive)
            || message.contains("Secondary capture", Qt::CaseSensitive)
            || message.contains("Master timecode type")
            || message.contains("Using LTC to", Qt::CaseSensitive)
            || message.contains("channel mode enabled", Qt::CaseSensitive)
            || message.contains("starting capture thread", Qt::CaseSensitive)
            || message.contains("fifo init/start completed", Qt::CaseSensitive)
            || message.contains("Recovered", Qt::CaseSensitive)
            || message.contains("dropped=0", Qt::CaseSensitive))
    {
        att = 1;
    }
    if(message.contains("Timestamp differs from expected", Qt::CaseSensitive)
            || message.contains("wait_for_good signal() returning", Qt::CaseSensitive)
            || message.contains("Need to recover", Qt::CaseSensitive)
            || message.contains("tc_diff=", Qt::CaseSensitive))
    {
        att = 3;
    }
    if(message.contains("SV_ERROR", Qt::CaseSensitive)
            && !message.contains("SYNC", Qt::CaseSensitive))
    {
        att = 2;
    }
    if(message.contains("SV_ERROR", Qt::CaseSensitive)
            && message.contains("SYNC", Qt::CaseSensitive))
    {
        att = 4;
    }
    return att;
}
