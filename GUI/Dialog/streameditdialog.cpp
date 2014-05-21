#include "streameditdialog.h"

streameditdialog::streameditdialog(QString ipAdd, QString streamID, QWidget *parent) :
    QWidget(parent)
{
    this->ipAdd = ipAdd;
    this->streamID = streamID;
    dialog = new QDialog();
    dialog->setWindowTitle(QString("%1%2%3").arg(this->ipAdd, ",Stream: ", this->streamID));
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);
    QObject::connect(cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
    table = new QTableWidget(10, 1);
    createTable();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(table, 0, 0, 10, 3);
    layout->addWidget(okButton, 10, 1);
    layout->addWidget(cancelButton, 10, 2);
    dialog->setLayout(layout);
}

void streameditdialog::createTable()
{
    QStringList headList;
    headList<<"Audio track"<<"Aspect"<<"Split Minutes"<<"Thumbnail"<<"Thumbnail pic per sec"
           <<"Channel Number"<<"Stream ID"<<"Enable"<<"Restart"<<"Project Number";
    table->setVerticalHeaderLabels(headList);
    table->horizontalHeader()->setVisible(false);
    audioEdit = new QSpinBox();
    audioEdit->setMaximum(8);
    audioEdit->setMinimum(0);
    table->setCellWidget(0, 0, audioEdit);
    aspectEdit = new QComboBox();
    aspectEdit->addItem("4:3");
    aspectEdit->addItem("16:9");
    table->setCellWidget(1, 0, aspectEdit);
    splitEdit = new QSpinBox();
    splitEdit->setMinimum(0);
    splitEdit->setMaximum(1440);
    table->setCellWidget(2, 0, splitEdit);
    thumEdit = new QCheckBox();
    thumEdit->setChecked(1);
    table->setCellWidget(3, 0, thumEdit);
    thumPPSEdit = new QSpinBox();
    thumPPSEdit->setMinimum(0);
    thumPPSEdit->setValue(1);
    thumPPSEdit->setEnabled(false);
    connect(thumEdit, SIGNAL(stateChanged(int)), this, SLOT(thumPPSEditEnabledSlot(int)));
    table->setCellWidget(4, 0, thumPPSEdit);
    channelEdit = new QSpinBox();
    channelEdit->setMaximum(16);
    channelEdit->setMinimum(0);
    table->setCellWidget(5, 0, channelEdit);
    streamEdit = new QSpinBox();
    streamEdit->setMaximum(32);
    streamEdit->setMinimum(0);
    table->setCellWidget(6, 0, streamEdit);
    enableEdit = new QCheckBox();
    table->setCellWidget(7, 0, enableEdit);
    restartEdit = new QCheckBox();
    table->setCellWidget(8, 0, restartEdit);
    projectNrEdit = new QSpinBox();
    projectNrEdit->setMinimum(-1);
    table->setCellWidget(9, 0, projectNrEdit);
}

void streameditdialog::setStream2Table(streamtype _stream)
{
    audioEdit->setValue(_stream.audioTrack);
    connect(audioEdit, SIGNAL(valueChanged(int)), this, SLOT(setOKButtonEnable()));
    if(_stream.aspect == "4:3")
        aspectEdit->setCurrentIndex(0);
    else
        aspectEdit->setCurrentIndex(1);
    connect(aspectEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(setOKButtonEnable()));
    splitEdit->setValue(_stream.split);
    connect(splitEdit, SIGNAL(valueChanged(int)), this, SLOT(setOKButtonEnable()));
    thumEdit->setChecked(_stream.thumb);
    connect(thumEdit, SIGNAL(stateChanged(int)), this, SLOT(setOKButtonEnable()));
    thumPPSEdit->setValue(_stream.thumPPS);
    connect(thumPPSEdit, SIGNAL(valueChanged(int)), this, SLOT(setOKButtonEnable()));
    channelEdit->setValue(_stream.channel);
    connect(channelEdit, SIGNAL(valueChanged(int)), this, SLOT(setOKButtonEnable()));
    streamEdit->setValue(_stream.streamID);
    connect(streamEdit, SIGNAL(valueChanged(int)), this, SLOT(setOKButtonEnable()));
    enableEdit->setChecked(_stream.enable);
    connect(enableEdit, SIGNAL(stateChanged(int)), this, SLOT(setOKButtonEnable()));
    restartEdit->setChecked(_stream.restart);
    connect(restartEdit, SIGNAL(stateChanged(int)), this, SLOT(setOKButtonEnable()));
    projectNrEdit->setValue(_stream.projectNr);
    connect(projectNrEdit, SIGNAL(valueChanged(int)), this, SLOT(setOKButtonEnable()));
}

void streameditdialog::thumPPSEditEnabledSlot(int _isEnable)
{
    thumPPSEdit->setEnabled(_isEnable);
}

void streameditdialog::setOKButtonEnable()
{
    this->okButton->setEnabled(true);
}
