#ifndef ERRORMESSAGES_H
#define ERRORMESSAGES_H

#include <QObject>
#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QGridLayout>
#include <config/messagetype.h>
#include <QDebug>
/**
    \brief the class defines the errormessages dialog
*/
class errormessages : public QObject
{
    Q_OBJECT
public:
    /**
    \brief initial the error message dialog
    */
    explicit errormessages();
    /**
    \brief initial the error message dialog with the parameters
    */
    errormessages(int type, QString ipAdd, QString videoCard = "-1", int channel = -1, QObject *parent = 0);
    /**
    \brief initial the error message dialog with the messagelist and type
    */
    errormessages(QList<messageType> messageList, int type);
    /**
    \brief
    \param dialog : dialog interface
    */
    QDialog* dialog;
    /**
    \brief
    \param table : format the components
    */
    QTableWidget* table;
    /**
    \brief
    \param type : the type of message dialog, 1 = GOOD, 2 = ERROR, 3 = WARNING, 4 = SYNC ERROR
    */
    int type;
    /**
    \brief
    \param ipAdd : the ip address of the server
    */
    QString ipAdd;
    /**
    \brief
    \param videoCard : the ID (name) of the video card
    */
    QString videoCard;
    /**
    \brief
    \param channel : the ID of the channel
    */
    int channel;
    /**
    \brief
    \param okButton : the button to close the dialog
    */
    QPushButton* okButton;
    /**
    \brief set the message in the table
    */
    void setTable(QList<messageType> messageList, int type);
    /**
    \brief clean all the message in the table
    */
    void cleanTable();
signals:

public slots:

};

#endif // ERRORMESSAGES_H
