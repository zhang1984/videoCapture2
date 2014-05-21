#include "errormessages.h"

errormessages::errormessages()
{
    table = new QTableWidget(999, 3);
    QStringList headList;
    headList<<"Datum"<<"Time"<<"Device"<<"Message";
    table->setHorizontalHeaderLabels(headList);
    table->horizontalHeader()->setStretchLastSection(true);

    okButton = new QPushButton("OK");
    dialog = new QDialog();
    dialog->setWindowTitle("Information");
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(table, 0, 0);
    layout->addWidget(okButton, 1, 2);
    dialog->setLayout(layout);
    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(close()));
}

errormessages::errormessages(int type, QString ipAdd, QString videoCard, int channel, QObject *parent) :
    QObject(parent)
{
    this->type = type;
    this->ipAdd = ipAdd;
    this->videoCard = videoCard;
    this->channel = channel;
    table = new QTableWidget();
    QStringList headList;
    headList<<"Datum"<<"Time"<<"Device"<<"Message";
    table->setHorizontalHeaderLabels(headList);
    table->horizontalHeader()->setStretchLastSection(true);

    okButton = new QPushButton("OK");
    dialog = new QDialog();
    dialog->setWindowTitle("Information");
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(table, 0, 0);
    layout->addWidget(okButton, 1, 2);
    dialog->setLayout(layout);
    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(close()));
}

errormessages::errormessages(QList<messageType> messageList, int type)
{
    table = new QTableWidget(0, 3);
    QStringList headList;
    headList<<"Datum"<<"Time"<<"Message";
    table->setHorizontalHeaderLabels(headList);
    table->horizontalHeader()->setStretchLastSection(true);
    this->setTable(messageList, type);
    okButton = new QPushButton("OK");
    dialog = new QDialog();
    dialog->setWindowTitle("Information");
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(table, 0, 0);
    layout->addWidget(okButton, 1, 2);
    dialog->setLayout(layout);
    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(close()));
}

void errormessages::setTable(QList<messageType> messageList, int type)
{
    cleanTable();
    int j = 0;
    for(int i = 0; i < messageList.count(); i++)
    {
        if(messageList.at(i).type == type)
        {
            table->insertRow(table->rowCount());
            QTableWidgetItem* item1 = new QTableWidgetItem();
            item1->setText(QString("%1").arg(messageList.at(i).datum));
            QTableWidgetItem* item2 = new QTableWidgetItem();
            item2->setText(messageList.at(i).time);
            QTableWidgetItem* item3 = new QTableWidgetItem();
            item3->setText(messageList.at(i).message);

            table->setItem(j, 0, item1);
            table->setItem(j, 1, item2);
            table->setItem(j, 2, item3);
            j++;
        }
    }
}

void errormessages::cleanTable()
{
    while(table->rowCount() != 0)
    {
        table->removeRow(0);
    }
}
