#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QDebug>
#include <config/servertype.h>
/**
\brief define the add dialog in GUI, for add the formatType in serverType
*/
class addDialog : public QObject
{
    Q_OBJECT
public:
    /**
    \brief initial the addDialog
    */
    explicit addDialog(QObject *parent = 0);
    /**
    \brief
    \param dialog : the dialog-interface for the addDialog
    */
    QDialog* dialog;
    /**
    \brief
    \param okButton : the button to accept the input
    */
    QPushButton* okButton;
    /**
      \brief
      \param cancelButton : the button to cancel the input
    */
    QPushButton* cancelButton;
    /**
    \brief
    \param attrTable : attribute table, a interface for the items input
    */
    QTableWidget* attrTable;
    /**
    \brief
    \param ipEdit : interface of the combobox chooses the existed server
    */
    QComboBox* ipEdit;
    /**
    \brief
    \param serverNameEdit : interface of the line edit shows the name of the server
    */
    QLineEdit* serverNameEdit;
    /**
    \brief
    \param projectNameEdit : interface of the line edit shows the name of the project
    */
    QLineEdit* projectNameEdit;
    /**
    \brief
    \param audioEdit : interface of the spin box for input the number of audio tracks, the value interval is between 0 - 8
    */
    QSpinBox* audioEdit;
    /**
    \brief
    \param channelEdit : interface of the spin box for input the ID of channel, the value interval is between 0 - 16
    */
    QSpinBox* channelEdit;
    /**
    \brief
    \param streamEdit : interface of the spin box for input the ID of the stream, the value interval is between 0 - 32
    */
    QSpinBox* streamEdit;
    /**
    \brief
    \param aspectEdit : interface of the combo box for the aviliable aspect choices
    */
    QComboBox* aspectEdit;
    /**
    \brief
    \param splitEdit : interface of the spin box for the split defineed, the value interval ist [0, 1440], 0 means the split is a day (1440 min)
    */
    QSpinBox* splitEdit;
    /**
    \brief
    \param thumEdit : interface of the checkbox for the thumbnail
    */
    QCheckBox* thumEdit;
    /**
    \brief
    \param thumPPSEdit : interface of the spin box for thumbnail_pic_per_sec, the value interval ist > 0
    */
    QSpinBox* thumPPSEdit;
    /**
    \brief
    \param codecEdit : interface of the combo box for resolution, includes "DNX120I_MXF_ATOM"
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
            <<"SD_MPEG4MP_AAC_MOV"
    */
    QComboBox* codecEdit;
    /**
    \brief
    \param tapeNameEdit : interface for define the default_tapename
    */
    QLineEdit* tapeNameEdit;
    /**
    \brief
    \param fileNameEdit : interface for define the defalut_filename
    */
    QLineEdit* fileNameEdit;
    /**
    \brief
    \param creatingpathEdit : interface for define the creatingpath
    */
    QLineEdit* creatingpathEdit;
    /**
    \brief
    \param archivPathEdit : interface for define the archiv_path
    */
    QLineEdit* archivPathEdit;
    /**
    \brief
    \param archivResultEdit : interface for define the archiv_result_path
    */
    QLineEdit* archivResultEdit;
    /**
    \brief
    \param scaleEdit : interface for define the scale
    */
    QLineEdit* scaleEdit;
    /**
    \brief
    \param videoBitEdit : interface for define the video_bitrate
    */
    QLineEdit* videoBitEdit;
    /**
    \brief
    \param audioBitEdit : interface for define the audio_bitrate
    */
    QLineEdit* audioBitEdit;
    /**
    \brief
    \param serverList : the list of servers, include all the formatTypes, streamtypes, cardtypes in the server
    */
    QList<serverType> serverList;
signals:

public slots:
    /**
    \brief the slot for insert the defined format into the serverList
    */
    void setServerListSlot(QList<serverType> serverList);
    /**
    \brief the slot for find the relative configuration of the server in serverList, and fill the editors
    */
    void setIPEditSlot(int index);
    /**
    \brief the slot for changing the status of thumEdit
    */
    void setThumbSlot(int);
    /**
    \brief the slot for changed the enable/disable status in formatType with Hi/Low Res in user interface
    */
    void setLowResSlot(int);
};

#endif // ADDDIALOG_H
