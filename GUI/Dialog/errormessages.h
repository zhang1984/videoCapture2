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

class errormessages : public QObject
{
    Q_OBJECT
public:
    explicit errormessages();
    errormessages(int type, QString ipAdd, QString videoCard = "-1", int channel = -1, QObject *parent = 0);
    errormessages(QList<messageType> messageList, int type);
    QDialog* dialog;
    QTableWidget* table;
    int type;
    QString ipAdd;
    QString videoCard;
    int channel;

    QPushButton* okButton;

    void setTable(QList<messageType> messageList, int type);
    void cleanTable();
signals:

public slots:

};

#endif // ERRORMESSAGES_H
