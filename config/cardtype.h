#ifndef CARDTYPE_H
#define CARDTYPE_H

#include <QString>
#include <QList>

/*!
  \brief
  define the card type
*/
class cardtype
{
public:
    /**
        \brief initial the class*/
    cardtype();
    /**
    \brief
    initial the class
    \param index : the index of the cardtype
    \param Name : the name of the class
    \param channelList : the list of channels, which under the card
    */
    cardtype(int index, QString Name, QList< int> channelList);

    int index;
    QString name;
    QList< int> channelList;

    /**
    \brief
    compare function, whether is the same card.
    */
    int compare(cardtype _card);

    /**
    \brief
    return the card name
    */
    QString getName(QList<cardtype> cardList, int index);

    /**
    \brief
    return the channel list under the card
    */
    QList<int> getChannelList(QList<cardtype> cardList, QString name);
};

#endif // CARDTYPE_H
