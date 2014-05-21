#include "servereditdialog.h"

serverEditDialog::serverEditDialog(QString ipAdd, QWidget *parent) :
    QWidget(parent)
{
    this->ipAdd = ipAdd;
    dialog = new QDialog();
    dialog->setWindowTitle(this->ipAdd);
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    QLabel* project_l = new QLabel("Project name");
    QLabel* server_l = new QLabel("Server name");
    projectNameEdit = new QLineEdit();
    serverNameEdit = new QLineEdit();
    videoCardTable = new QTableWidget(4, 3);
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);
    QObject::connect(cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
    createTable();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(project_l, 0, 0);
    layout->addWidget(projectNameEdit, 0, 1);
    layout->addWidget(server_l, 1, 0);
    layout->addWidget(serverNameEdit, 1, 1);
    layout->addWidget(videoCardTable, 2, 0, 5, 3);
    layout->addWidget(okButton, 7, 1);
    layout->addWidget(cancelButton, 7, 2);
    dialog->setLayout(layout);
}

void serverEditDialog::createTable()
{
    QStringList headList;
    headList<<"Video Card"<<"Name"<<"Channels";
    videoCardTable->setHorizontalHeaderLabels(headList);
    videoCardTable->verticalHeader()->setVisible(false);
    /*
    QTableWidgetItem* item1 = new QTableWidgetItem("1");
    item1->setFlags(item1->flags() &~Qt::ItemIsEditable);
    item1->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* item2 = new QTableWidgetItem("2");
    item2->setFlags(item1->flags() &~Qt::ItemIsEditable);
    item2->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* item3 = new QTableWidgetItem("3");
    item3->setFlags(item1->flags() &~Qt::ItemIsEditable);
    item3->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* item4 = new QTableWidgetItem("4");
    item4->setFlags(item4->flags() &~Qt::ItemIsEditable);
    item4->setTextAlignment(Qt::AlignCenter);
    videoCardTable->setItem(0, 0, item1);
    videoCardTable->setItem(1, 0, item2);
    videoCardTable->setItem(2, 0, item3);
    videoCardTable->setItem(3, 0, item4);*/
}

QList<cardtype> serverEditDialog::table2CardList()
{
    int i = 0;
    QList<cardtype> cardList;
    QTableWidgetItem* item = new QTableWidgetItem();
    item = videoCardTable->item(i, 0);
    while(item != 0)
    {
        cardtype card;
        card.index = videoCardTable->item(i, 0)->text().toInt();
        card.name = videoCardTable->item(i, 1)->text();
        QList<int> channelList;
        QString channel = videoCardTable->item(i, 2)->text();
        for(int i = 0; i < channel.split(" ").count(); i++)
        {
            channelList.append(channel.split(" ").at(i).toInt());
        }
        card.channelList = channelList;
        cardList.append(card);
        i++;
        item = videoCardTable->item(i, 0);
    }
    return cardList;
}

void serverEditDialog::setOKButtonEnable()
{
    this->okButton->setEnabled(true);
}
