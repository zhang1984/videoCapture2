#include "adddialog.h"

addDialog::addDialog(QObject *parent) :
    QObject(parent)
{
    dialog = new QDialog();
    dialog->setWindowTitle("Add...");
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    QStringList codecList;
    codecList<<"DNX120I_MXF_ATOM"
            <<"DNX185I_MXF_ATOM"
            <<"DV25_RAW"
            <<"DV25_MXF_ATOM"
            <<"DV25_MOV"
            <<"DV50_RAW"
            <<"DV50_MXF_ATOM"
            <<"DV50_MOV"
            <<"DV100_RAW"
            <<"DV100_MXF_ATOM"
            <<"DV100_MOV"
            <<"MJPEG21_MXF_ATOM"
            <<"MJPEG31_MXF_ATOM"
            <<"MJPEG101_MXF_ATOM"
            <<"MJPEG101M_MXF_ATOM"
            <<"MJPEG151S_MXF_ATOM"
            <<"MJPEG201_MXF_ATOM"
            <<"SD_MPEG4BP_AAC_MOV"
            <<"SD_MPEG4MP_AAC_MOV";
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    QStringList tableVerList;
    attrTable = new QTableWidget(20, 2);
    tableVerList<<"IP"<<"Server name"<<"Project name"<<"Channel Number"<<"Stream ID"<<"Audio Track"
               <<"Aspect"<<"Split Minutes"<<"Thumbnail"<<"Thumbnail pic per sec"<<"Codec"<<"Tape name"
              <<"File name"<<"Creating Path"<<"Archiv path"<<"Archiv result path"<<"Scale edit"<<"Video bitrate"<<"Audio bitrate";
    for(int i = 0; i < tableVerList.count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(tableVerList.at(i));
        attrTable->setItem(i, 0, item);
        //attrTable->item(i, 0)->setText(tableVerList.at(i));
        attrTable->item(i, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

    ipEdit = new QComboBox();
    //ipEdit->setInputMask("000.000.000.000");
    attrTable->setCellWidget(0, 1, ipEdit);
    serverNameEdit = new QLineEdit();
    serverNameEdit->setEnabled(false);
    attrTable->setCellWidget(1, 1, serverNameEdit);
    //videoCardEdit = new QLineEdit();
    //attrTable->setCellWidget(2, 1, videoCardEdit);
    projectNameEdit = new QLineEdit();
    projectNameEdit->setEnabled(false);
    attrTable->setCellWidget(2, 1, projectNameEdit);
    channelEdit = new QSpinBox();
    channelEdit->setMaximum(16);
    channelEdit->setMinimum(0);
    attrTable->setCellWidget(3, 1, channelEdit);
    streamEdit = new QSpinBox();
    streamEdit->setMaximum(32);
    streamEdit->setMinimum(0);
    attrTable->setCellWidget(4, 1, streamEdit);
    audioEdit = new QSpinBox();
    audioEdit->setMaximum(8);
    audioEdit->setMinimum(0);
    attrTable->setCellWidget(5, 1, audioEdit);
    aspectEdit = new QComboBox();
    aspectEdit->addItem("4:3");
    aspectEdit->addItem("16:9");
    attrTable->setCellWidget(6, 1, aspectEdit);
    splitEdit = new QSpinBox();
    splitEdit->setMinimum(0);
    splitEdit->setMaximum(1440);
    attrTable->setCellWidget(7, 1, splitEdit);
    thumEdit = new QCheckBox();
    thumEdit->setChecked(false);
    attrTable->setCellWidget(8, 1, thumEdit);
    thumPPSEdit = new QSpinBox();
    thumPPSEdit->setMinimum(0);
    thumPPSEdit->setValue(1);
    thumPPSEdit->setEnabled(false);
    connect(thumEdit, SIGNAL(stateChanged(int)), this, SLOT(setThumbSlot(int)));
    attrTable->setCellWidget(9, 1, thumPPSEdit);
    codecEdit = new QComboBox();
    codecEdit->addItems(codecList);
    attrTable->setCellWidget(10, 1, codecEdit);
    tapeNameEdit = new QLineEdit();
    attrTable->setCellWidget(11, 1, tapeNameEdit);
    fileNameEdit = new QLineEdit();
    attrTable->setCellWidget(12, 1, fileNameEdit);
    creatingpathEdit  = new QLineEdit();
    attrTable->setCellWidget(13, 1, creatingpathEdit);
    archivPathEdit = new QLineEdit();
    attrTable->setCellWidget(14, 1, archivPathEdit);
    archivResultEdit = new QLineEdit();
    attrTable->setCellWidget(15, 1, archivResultEdit);
    scaleEdit = new QLineEdit();
    scaleEdit->setInputMask("000:000");
    scaleEdit->setEnabled(false);
    attrTable->setCellWidget(16, 1, scaleEdit);
    videoBitEdit = new QLineEdit();
    videoBitEdit->setInputMask("0000");
    videoBitEdit->setEnabled(false);
    attrTable->setCellWidget(17, 1, videoBitEdit);
    audioBitEdit = new QLineEdit();
    audioBitEdit->setInputMask("000");
    audioBitEdit->setEnabled(false);
    attrTable->setCellWidget(18, 1, audioBitEdit);
    attrTable->verticalHeader()->setVisible(false);
    //attrTable->verticalHeader()->setStretchLastSection(true);
    attrTable->verticalHeader()->adjustSize();
    attrTable->horizontalHeader()->setVisible(false);
    attrTable->horizontalHeader()->setStretchLastSection(true);
    attrTable->horizontalHeader()->adjustSize();
    connect(codecEdit, SIGNAL(activated(int)), this, SLOT(setLowResSlot(int)));

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(attrTable, 0, 0, 20, 2);
    layout->addWidget(okButton, 19, 0, 1, 1);
    layout->addWidget(cancelButton, 19, 1, 1, 1);

    QObject::connect(cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
    dialog->setLayout(layout);
}

void addDialog::setServerListSlot(QList<serverType> serverList)
{
    ipEdit->clear();
    for(int i = 0; i < serverList.count(); i++)
    {
        ipEdit->addItem(serverList.at(i).ipAdd);
    }
    this->serverList = serverList;
    serverNameEdit->setText(serverList.at(0).serverName);
    projectNameEdit->setText(serverList.at(0).projectName);
    connect(ipEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(setIPEditSlot(int)));
}

void addDialog::setIPEditSlot(int index)
{
    serverNameEdit->setText(serverList.at(index).serverName);
    projectNameEdit->setText(serverList.at(index).projectName);
}

void addDialog::setThumbSlot(int isChecked)
{
    this->thumPPSEdit->setEnabled(isChecked);
}

void addDialog::setLowResSlot(int index)
{
    if(index <  17)
    {
        videoBitEdit->setEnabled(false);
        audioBitEdit->setEnabled(false);
        scaleEdit->setEnabled(false);
    }
    else
    {
        videoBitEdit->setEnabled(true);
        audioBitEdit->setEnabled(true);
        scaleEdit->setEnabled(true);
    }
}
