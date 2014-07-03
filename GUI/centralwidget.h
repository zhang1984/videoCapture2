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


class centralwidget : public QWidget
{
    Q_OBJECT
public:
    explicit centralwidget(QWidget *parent = 0);
    QWidget* centralWidget;
    QStringList codecList;
    QLCDNumber* currentTimeDisplay;
    QLCDNumber* durationDisplay;
    QLCDNumber* lastSplitDisplay;
    QLCDNumber* nextSplitDisplay;
    QLabel* captureLabel;
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

    void setData(serverType _server);
    void setData(serverType _server, streamtype _stream);
    void setData(serverType _server, streamtype _stream, formatType _format);

    int setFileControl(QString ipAdd);
signals:

public slots:
    void updateTime();

};

#endif // CENTRALWIDGET_H
