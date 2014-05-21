#include "centralwidget.h"

centralwidget::centralwidget(QWidget *parent) :
    QWidget(parent)
{
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
    createTimeWidget();
    createTable();
    //QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_timeWidget);
    layout->addWidget(attrTable);
    //widget->setLayout(layout);
    centralWidget = new QWidget();
    centralWidget->setLayout(layout);
}

void centralwidget::createTimeWidget()
{
    QGridLayout* layout = new QGridLayout();

    currentTimeDisplay = new QLCDNumber();
    currentTimeDisplay->setSegmentStyle(QLCDNumber::Flat);
    currentTimeDisplay->setDigitCount(11);
    currentTimeDisplay->setMode(QLCDNumber::Dec);
    QLabel* currentTime_l = new QLabel("Current time");
    currentTime_l->setFrameStyle(QFrame::Sunken);
    currentTime_l->setStyleSheet("QLabel {background-color: black; color: white}");
    currentTime_l->setAlignment(Qt::AlignCenter);

    durationDisplay = new QLCDNumber();
    durationDisplay->setSegmentStyle(QLCDNumber::Flat);
    durationDisplay->setDigitCount(11);
    durationDisplay->setMode(QLCDNumber::Dec);
    QLabel* duration_l = new QLabel("Duration");
    duration_l->setFrameStyle(QFrame::Sunken);
    duration_l->setStyleSheet("QLabel {background-color: black; color: white}");
    duration_l->setAlignment(Qt::AlignCenter);

    lastSplitDisplay = new QLCDNumber();
    lastSplitDisplay->setSegmentStyle(QLCDNumber::Flat);
    lastSplitDisplay->setDigitCount(8);
    lastSplitDisplay->setMode(QLCDNumber::Dec);
    QLabel* lastSplit_l = new QLabel("Last split");
    lastSplit_l->setFrameStyle(QFrame::Sunken);
    lastSplit_l->setStyleSheet("QLabel {background-color: black; color: white}");
    lastSplit_l->setAlignment(Qt::AlignCenter);

    nextSplitDisplay = new QLCDNumber();
    nextSplitDisplay->setSegmentStyle(QLCDNumber::Flat);
    nextSplitDisplay->setDigitCount(8);
    nextSplitDisplay->setMode(QLCDNumber::Dec);
    QLabel* nextSplit_l = new QLabel("Next split");
    nextSplit_l->setFrameStyle(QFrame::Sunken);
    nextSplit_l->setStyleSheet("QLabel {background-color: black; color: white}");
    nextSplit_l->setAlignment(Qt::AlignCenter);

    QGridLayout* layout1 = new QGridLayout();
    layout1->addWidget(currentTime_l, 0,  0);
    layout1->addWidget(currentTimeDisplay,1, 0);
    layout1->addWidget(lastSplit_l, 2, 0);
    layout1->addWidget(lastSplitDisplay, 3, 0);
    layout1->addWidget(duration_l, 0, 2);
    layout1->addWidget(durationDisplay, 1, 2);
    layout1->addWidget(nextSplit_l, 2, 2);
    layout1->addWidget(nextSplitDisplay, 3, 2);
    layout->addLayout(layout1, 0, 0, 1, 4);


    captureLabel = new QLabel();
    QImage imageObj;
    imageObj.load(":resource/capture_icon.png");
    imageObj.scaledToHeight(128);
    captureLabel->setPixmap(QPixmap::fromImage(imageObj));
    captureLabel->setEnabled(true);
    layout->addWidget(captureLabel, 0, 4, 1, 1);
    _timeWidget = new QWidget();
    _timeWidget->setLayout(layout);
}

void centralwidget::createTable()
{
    QStringList tableVerList;
    attrTable = new QTableWidget(20, 2);
    tableVerList<<"IP"<<"Server name"<<"Video Card"<<"Project name"<<"Channel Number"<<"Stream ID"<<"Audio Track"
               <<"Aspect"<<"Split Minutes"<<"Thumbnail"<<"Thumbnail pic per sec"<<"Codec"<<"Tape name"
              <<"File name"<<"Creating Path"<<"Archiv path"<<"Archiv result path"<<"Scale edit"<<"Video bitrate"<<"Audio bitrate";
    for(int i = 0; i < tableVerList.count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(tableVerList.at(i));
        attrTable->setItem(i, 0, item);
        //attrTable->item(i, 0)->setText(tableVerList.at(i));
        attrTable->item(i, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

    ipEdit = new QLineEdit();
#ifdef _WIN32_
    ipEdit->setInputMask("000.000.000.000");
#endif
    attrTable->setCellWidget(0, 1, ipEdit);
    serverNameEdit = new QLineEdit();
    attrTable->setCellWidget(1, 1, serverNameEdit);
    videoCardEdit = new QLineEdit();
    attrTable->setCellWidget(2, 1, videoCardEdit);
    projectNameEdit = new QLineEdit();
    attrTable->setCellWidget(3, 1, projectNameEdit);
    channelEdit = new QSpinBox();
    channelEdit->setMaximum(16);
    channelEdit->setMinimum(0);
    attrTable->setCellWidget(4, 1, channelEdit);
    streamEdit = new QSpinBox();
    streamEdit->setMaximum(32);
    streamEdit->setMinimum(0);
    attrTable->setCellWidget(5, 1, streamEdit);
    audioEdit = new QSpinBox();
    audioEdit->setMaximum(8);
    audioEdit->setMinimum(0);
    attrTable->setCellWidget(6, 1, audioEdit);
    aspectEdit = new QComboBox();
    aspectEdit->addItem("4:3");
    aspectEdit->addItem("16:9");
    attrTable->setCellWidget(7, 1, aspectEdit);
    splitEdit = new QSpinBox();
    splitEdit->setMinimum(0);
    splitEdit->setMaximum(1440);
    attrTable->setCellWidget(8, 1, splitEdit);
    thumEdit = new QCheckBox();
    thumEdit->setChecked(false);
    attrTable->setCellWidget(9, 1, thumEdit);
    thumPPSEdit = new QSpinBox();
    thumPPSEdit->setMinimum(0);
    thumPPSEdit->setValue(1);
    thumPPSEdit->setEnabled(false);
    attrTable->setCellWidget(10, 1, thumPPSEdit);
    codecEdit = new QComboBox();
    codecEdit->addItems(codecList);
    attrTable->setCellWidget(11, 1, codecEdit);
    tapeNameEdit = new QLineEdit();
    attrTable->setCellWidget(12, 1, tapeNameEdit);
    fileNameEdit = new QLineEdit();
    attrTable->setCellWidget(13, 1, fileNameEdit);
    creatingpathEdit  = new QLineEdit();
    attrTable->setCellWidget(14, 1, creatingpathEdit);
    archivPathEdit = new QLineEdit();
    attrTable->setCellWidget(15, 1, archivPathEdit);
    archivResultEdit = new QLineEdit();
    attrTable->setCellWidget(16, 1, archivResultEdit);
    scaleEdit = new QLineEdit();
    scaleEdit->setInputMask("000:000");
    attrTable->setCellWidget(17, 1, scaleEdit);
    videoBitEdit = new QLineEdit();
    videoBitEdit->setInputMask("0000");
    attrTable->setCellWidget(18, 1, videoBitEdit);
    audioBitEdit = new QLineEdit();
    audioBitEdit->setInputMask("000");
    attrTable->setCellWidget(19, 1, audioBitEdit);
    attrTable->verticalHeader()->setVisible(false);
    //attrTable->verticalHeader()->setStretchLastSection(true);
    attrTable->verticalHeader()->adjustSize();
    attrTable->horizontalHeader()->setVisible(false);
    attrTable->horizontalHeader()->setStretchLastSection(true);
    attrTable->horizontalHeader()->adjustSize();
}

void centralwidget::setData(serverType _server, streamtype _stream, formatType _format)
{
    ipEdit->setText(_server.ipAdd);
    serverNameEdit->setText(_server.serverName);
    projectNameEdit->setText(_server.projectName);
    videoCardEdit->setText(_server.getVideoCard(_stream.channel));
    audioEdit->setValue(_stream.audioTrack);
    channelEdit->setValue(_stream.channel);
    streamEdit->setValue(_stream.streamID);
    if(_stream.aspect == "4:3")
        aspectEdit->setCurrentIndex(0);
    else
        aspectEdit->setCurrentIndex(1);
    splitEdit->setValue(_stream.split);
    thumEdit->setChecked(_stream.thumb);
    thumPPSEdit->setValue(_stream.thumPPS);
    codecEdit->setCurrentText(_format.codec);
    tapeNameEdit->setText(_format.tapeName);
    fileNameEdit->setText(_format.fileName);
    creatingpathEdit->setText(_format.creatingPath);
    archivPathEdit->setText(_format.archivPath);
    archivResultEdit->setText(_format.archivResultPath);
    scaleEdit->setText(_format.scale);
    videoBitEdit->setText(QString("%1").arg(_format.videoBit));
    audioBitEdit->setText(QString("%1").arg(_format.audioBit));
}

void centralwidget::setData(serverType _server, streamtype _stream)
{
    ipEdit->setText(_server.ipAdd);
    serverNameEdit->setText(_server.serverName);
    projectNameEdit->setText(_server.projectName);
    videoCardEdit->setText(_server.getVideoCard(_stream.channel));
    audioEdit->setValue(_stream.audioTrack);
    channelEdit->setValue(_stream.channel);
    streamEdit->setValue(_stream.streamID);
    if(_stream.aspect == "4:3")
        aspectEdit->setCurrentIndex(0);
    else
        aspectEdit->setCurrentIndex(1);
    splitEdit->setValue(_stream.split);
    thumEdit->setChecked(_stream.thumb);
    thumPPSEdit->setValue(_stream.thumPPS);


}

void centralwidget::setData(serverType _server)
{
    ipEdit->setText(_server.ipAdd);
    serverNameEdit->setText(_server.serverName);
    projectNameEdit->setText(_server.projectName);
}
