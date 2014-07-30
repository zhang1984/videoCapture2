#ifndef STREAMEDITDIALOG_H
#define STREAMEDITDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QDialog>
#include <QHeaderView>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <config/streamtype.h>
#include <QDebug>
/**
\brief the dialog for stream edit
*/
class streameditdialog : public QWidget
{
    Q_OBJECT
public:
    /**
    \brief initial the class
    */
    explicit streameditdialog(QString ipAdd, QString streamID, QWidget *parent = 0);
    /**
    \brief
    \param ipAdd : ip address of the server
    */
    QString ipAdd;
    /**
    \brief
    \param streamID : stream_id
    */
    QString streamID;
    /**
    \brief
    \param table : the user interface as table layout
    */
    QTableWidget* table;
    /**
    \brief
    \param dialog : the popout window
    */
    QDialog* dialog;
    /**
    \brief
    \param okButton : accepet button
    */
    QPushButton* okButton;
    /**
    \brief
    \param cancelButton : cancel button
    */
    QPushButton* cancelButton;
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
    \param projectNrEdit : interface of the spin box for project_nr
    */
    QSpinBox* projectNrEdit;
    /**
    \brief
    \param enableEdit : interface of the checkbox for "enable"
    */
    QCheckBox* enableEdit;
    /**
    \brief
    \param enableEdit : interface of the checkbox for "restart"
    */
    QCheckBox* restartEdit;
    /**
    \brief create the table components in initial phase
    */
    void createTable();
    /**
    \brief automatic fill all the data of a streamtype into components
    */
    void setStream2Table(streamtype _stream);
signals:

public slots:
    /**
    \brief set thumPPSEdit is enabled if thumEdit is checked
    */
    void thumPPSEditEnabledSlot(int);
    /**
    \brief set okButton enabled if the components value changed
    */
    void setOKButtonEnable();

};

#endif // STREAMEDITDIALOG_H
