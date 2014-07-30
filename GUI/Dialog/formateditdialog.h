#ifndef FORMATEDITDIALOG_H
#define FORMATEDITDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QDialog>
#include <QHeaderView>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <config/formattype.h>
/**
\brief
the class defines a format edit dialog, for a specific format editting
*/
class formateditdialog : public QWidget
{
    Q_OBJECT
public:
    /**
    \brief initial a format edit dialog with the parameters
    */
    explicit formateditdialog(QString ipAdd, QString streamID, QString format, QWidget *parent = 0);
    /**
    \brief
    \param ipAdd : ip addresse or the server name
    */
    QString ipAdd;
    /**
    \brief
    \param streamID : the ID of the stream
    */
    QString streamID;
    /**
    \brief
    \param format : the name of the format, usually use the resolution name instead
    */
    QString format;
    /**
    \brief
    \param table : the table widget to layout the components in GUI
    */
    QTableWidget* table;
    /**
    \brief
    \param dialog : the dialog widget supplies a window to pop-out
    */
    QDialog* dialog;
    /**
    \brief
    \param okButton : Button object to close the dialog, and accept the format change
    */
    QPushButton* okButton;
    /**
    \brief
    \param cancelButton : Button object to close the dialog without the format change
    */
    QPushButton* cancelButton;
    /**
    \brief
    \param codecEdit : the combo box ojbect for choosing the resolution of the format
    */
    QComboBox* codecEdit;
    /**
    \brief
    \param tapeNameEdit : the line edit ojbect for editting the default_tapename
    */
    QLineEdit* tapeNameEdit;
    /**
    \brief
    \param tapeNameEdit : the line edit ojbect for editting the default_filename
    */
    QLineEdit* fileNameEdit;
    /**
    \brief
    \param creatingpathEdit : the line edit object for editting the creating_path
    */
    QLineEdit* creatingpathEdit;
    /**
    \brief
    \param archivPathEdit : the line edit ojbect for editting the archiv_path
    */
    QLineEdit* archivPathEdit;
    /**
    \brief
    \param archivResultEdit : the line edit ojbect for editting the archiv_result_path
    */
    QLineEdit* archivResultEdit;
    /**
    \brief
    \param scaleEdit : the line edit ojbect for editting the scale
    */
    QLineEdit* scaleEdit;
    /**
    \brief
    \param videoBitEdit : the line edit object for editting the video_bitrate
    */
    QLineEdit* videoBitEdit;
    /**
    \brief
    \param audioBitEdit : the line edit object for editting the audio_bitrate
    */
    QLineEdit* audioBitEdit;
    /**
    \brief
    \param timeoverlayEdit : the line edit object for editting the timeoverlay
    */
    QSpinBox* timeoverlayEdit;
    /**
    \brief creating the table layout, initial the GUI-Object in initial phase
    */
    void createTable();
    /**
    \brief set the format to the table, the configuration data are automatic filled in
    */
    void setFormat2Table(formatType _format);
signals:

public slots:
    /**
    \brief the slot for codecEdit, set the scaleEdit, videoBitEdit und audioBitEdit disable
    */
    void hiResSlot(int);
    /**
    \brief the slot for okButton, if the edits changed, set the button enable
    */
    void setOKButtonEnable();

};

#endif // FORMATEDITDIALOG_H
