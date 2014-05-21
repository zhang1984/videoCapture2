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

class streameditdialog : public QWidget
{
    Q_OBJECT
public:
    explicit streameditdialog(QString ipAdd, QString streamID, QWidget *parent = 0);
    QString ipAdd;
    QString streamID;
    QTableWidget* table;
    QDialog* dialog;
    QPushButton* okButton;
    QPushButton* cancelButton;

    QSpinBox* audioEdit;
    QSpinBox* channelEdit;
    QSpinBox* streamEdit;
    QComboBox* aspectEdit;
    QSpinBox* splitEdit;
    QCheckBox* thumEdit;
    QSpinBox* thumPPSEdit;
    QSpinBox* projectNrEdit;
    QCheckBox* enableEdit;
    QCheckBox* restartEdit;
    void createTable();
    void setStream2Table(streamtype _stream);
signals:

public slots:
    void thumPPSEditEnabledSlot(int);
    void setOKButtonEnable();

};

#endif // STREAMEDITDIALOG_H
