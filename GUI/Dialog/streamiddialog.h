#ifndef STREAMIDDIALOG_H
#define STREAMIDDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <QDebug>
class streamiddialog : public QWidget
{
    Q_OBJECT
public:
    explicit streamiddialog(QWidget *parent = 0);
    QDialog* dialog;
    QPushButton* okButton;

    QLineEdit* idEdit;
    QString id;
signals:

public slots:

    void getIDSlot();

};

#endif // STREAMIDDIALOG_H
