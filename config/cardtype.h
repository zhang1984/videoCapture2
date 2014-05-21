#ifndef CARDTYPE_H
#define CARDTYPE_H

#include <QString>
#include <QList>

class cardtype
{
public:
    cardtype();
    cardtype(int index, QString Name, QList< int> channelList);
    int index;
    QString name;
    QList< int> channelList;

    int compare(cardtype _card);
    QString getName(QList<cardtype> cardList, int index);
    QList<int> getChannelList(QList<cardtype> cardList, QString name);
};

#endif // CARDTYPE_H
