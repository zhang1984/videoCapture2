#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QStandardItemModel>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QList>
#include <QHeaderView>
#include <QScrollBar>
#include <config/servertype.h>
#include <thread/timeupdate.h>
#include <config/filecontrol.h>
#include <tuple>

/**
    define a widget shows items options
*/
class centralwidget : public QWidget
{
    Q_OBJECT
public:
    /**
    \brief initial the centralwidget
    */
    explicit centralwidget(QWidget *parent = 0);
    /**
    \brief
    \param the widget of the class
    */
    QWidget* centralWidget;
    /**
    \brief
    \param codecList : the list of all the resolutions
    */
    QStringList codecList;
    /**
    \brief
    \param currentTimeDisplay : the LCD display for current time
    */
    QLCDNumber* currentTimeDisplay;
    /**
    \brief
    \param durationDisplay : the LCD display for duration
    */
    QLCDNumber* durationDisplay;
    /**
    \brief
    \param lastSplitDisplay : the LCD display for last split
    */
    QLCDNumber* lastSplitDisplay;
    /**
    \brief
    \param nextSplitDisplay : the LCD display for next split
    */
    QLCDNumber* nextSplitDisplay;

    QLabel* captureLabel;

    /**
    \brief
    \param _timeWidget : the widget for the all timecode display layout
    */
    QWidget* _timeWidget;

    QTableWidget* attrTable;
    QLineEdit* ipEdit;
    QLineEdit* serverNameEdit;
    QLineEdit* projectNameEdit;
    QLineEdit* videoCardEdit;
    QSpinBox* audioEdit;
    QSpinBox* channelEdit;
    QSpinBox* streamEdit;
    QComboBox* aspectEdit;
    QSpinBox* splitEdit;
    QCheckBox* thumEdit;
    QSpinBox* thumPPSEdit;
    QComboBox* codecEdit;
    QLineEdit* tapeNameEdit;
    QLineEdit* fileNameEdit;
    QLineEdit* creatingpathEdit;
    QLineEdit* archivPathEdit;
    QLineEdit* archivResultEdit;
    QLineEdit* scaleEdit;
    QLineEdit* videoBitEdit;
    QLineEdit* audioBitEdit;
    timeUpdate* _timeUpdate;
    filecontrol* _fileControl;


    void createTimeWidget();
    void createTable();
    /**
    \brief set the server option in widget
    */
    void setData(serverType _server);
    /**
      \brief set the server and stream option in widget
    */
    void setData(serverType _server, streamtype _stream);
    /**
      \brief set the server, stream and format option in widget
    */
    void setData(serverType _server, streamtype _stream, formatType _format);
    /**
    \brief test, if the status.xml is enabled, yes, return 1, else return 0
    */
    int setFileControl(QString ipAdd);
signals:

public slots:
    /**
    \brief update the timecode in display from status.xml
    */
    void updateTime();

};

#endif // CENTRALWIDGET_H
