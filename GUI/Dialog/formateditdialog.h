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

class formateditdialog : public QWidget
{
    Q_OBJECT
public:
    explicit formateditdialog(QString ipAdd, QString streamID, QString format, QWidget *parent = 0);
    QString ipAdd;
    QString streamID;
    QString format;

    QTableWidget* table;
    QDialog* dialog;
    QPushButton* okButton;
    QPushButton* cancelButton;

    QComboBox* codecEdit;
    QLineEdit* tapeNameEdit;
    QLineEdit* fileNameEdit;
    QLineEdit* creatingpathEdit;
    QLineEdit* archivPathEdit;
    QLineEdit* archivResultEdit;
    QLineEdit* scaleEdit;
    QLineEdit* videoBitEdit;
    QLineEdit* audioBitEdit;
    QSpinBox* timeoverlayEdit;

    void createTable();
    void setFormat2Table(formatType _format);
signals:

public slots:
    void hiResSlot(int);
    void setOKButtonEnable();

};

#endif // FORMATEDITDIALOG_H
