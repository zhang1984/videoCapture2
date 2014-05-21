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

class addDialog : public QObject
{
    Q_OBJECT
public:
    explicit addDialog(QObject *parent = 0);
    QDialog* dialog;
    QPushButton* okButton;
    QPushButton* cancelButton;

    QTableWidget* attrTable;

    QComboBox* ipEdit;
    QLineEdit* serverNameEdit;
    QLineEdit* projectNameEdit;
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

    QList<serverType> serverList;
signals:

public slots:
    void setServerListSlot(QList<serverType> serverList);
    void setIPEditSlot(int index);
    void setThumbSlot(int);
    void setLowResSlot(int);
};

#endif // ADDDIALOG_H
