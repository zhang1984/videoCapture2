#include "formateditdialog.h"

formateditdialog::formateditdialog(QString ipAdd, QString streamID, QString format, QWidget *parent) :
    QWidget(parent)
{
    this->ipAdd = ipAdd;
    this->streamID = streamID;
    this->format = format;
    dialog = new QDialog();
    dialog->setWindowTitle(QString("%1%2%3%4%5").arg(this->ipAdd, ", Stream: ", this->streamID, ", Format: ", this->format));
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);
    QObject::connect(cancelButton, SIGNAL(clicked()), dialog, SLOT(close()));
    table = new QTableWidget(10, 1);
    createTable();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(table, 0, 0, 10, 5);
    layout->addWidget(okButton, 10, 3);
    layout->addWidget(cancelButton, 10, 4);
    dialog->setLayout(layout);
}

void formateditdialog::createTable()
{
    QStringList headList;
    headList<<"Codec"<<"Tape name"<<"File name"<<"Creating Path"<<"Archiv path"<<"Archiv result path"
           <<"Scale edit"<<"Video bitrate"<<"Audio bitrate"<<"Timecode overlay";
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

    table->setVerticalHeaderLabels(headList);
    table->horizontalHeader()->setVisible(false);
    codecEdit = new QComboBox();
    codecEdit->addItems(codecList);
    table->setCellWidget(0, 0, codecEdit);
    tapeNameEdit = new QLineEdit();
    table->setCellWidget(1, 0, tapeNameEdit);
    fileNameEdit = new QLineEdit();
    table->setCellWidget(2, 0, fileNameEdit);
    creatingpathEdit  = new QLineEdit();
    table->setCellWidget(3, 0, creatingpathEdit);
    archivPathEdit = new QLineEdit();
    table->setCellWidget(4, 0, archivPathEdit);
    archivResultEdit = new QLineEdit();
    table->setCellWidget(5, 0, archivResultEdit);
    scaleEdit = new QLineEdit();
    scaleEdit->setInputMask("000:000");
    table->setCellWidget(6, 0, scaleEdit);
    videoBitEdit = new QLineEdit();
    videoBitEdit->setInputMask("0000");
    table->setCellWidget(7, 0, videoBitEdit);
    audioBitEdit = new QLineEdit();
    audioBitEdit->setInputMask("000");
    table->setCellWidget(8, 0, audioBitEdit);
    timeoverlayEdit = new QSpinBox();
    table->setCellWidget(9, 0, timeoverlayEdit);
    table->horizontalHeader()->setStretchLastSection(true);
    connect(codecEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(hiResSlot(int)));
}

void formateditdialog::setFormat2Table(formatType _format)
{
    codecEdit->setCurrentText(_format.codec);
    connect(codecEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(setOKButtonEnable()));
    tapeNameEdit->setText(_format.tapeName);
    connect(tapeNameEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    fileNameEdit->setText(_format.fileName);
    connect(fileNameEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    creatingpathEdit->setText(_format.creatingPath);
    connect(creatingpathEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    archivPathEdit->setText(_format.archivPath);
    connect(archivPathEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    archivResultEdit->setText(_format.archivResultPath);
    connect(archivResultEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    scaleEdit->setText(_format.scale);
    connect(scaleEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    videoBitEdit->setText(QString("%1").arg(_format.videoBit));
    connect(videoBitEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    audioBitEdit->setText(QString("%1").arg(_format.audioBit));
    connect(audioBitEdit, SIGNAL(textChanged(QString)), this, SLOT(setOKButtonEnable()));
    timeoverlayEdit->setValue(_format.timeOverlay);
    connect(timeoverlayEdit, SIGNAL(valueChanged(int)), this, SLOT(setOKButtonEnable()));
}

void formateditdialog::hiResSlot(int resIndex)
{
    if(resIndex <= 16)
    {
        scaleEdit->setEnabled(false);
        videoBitEdit->setEnabled(false);
        audioBitEdit->setEnabled(false);
    }
    else
    {
        scaleEdit->setEnabled(false);
        videoBitEdit->setEnabled(false);
        audioBitEdit->setEnabled(false);
    }
}

void formateditdialog::setOKButtonEnable()
{
    okButton->setEnabled(true);
}
