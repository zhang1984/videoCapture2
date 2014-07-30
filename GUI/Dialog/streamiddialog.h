#ifndef STREAMIDDIALOG_H
#define STREAMIDDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <QDebug>
/**
\brief the class of server id dialog, the parameter in config.xml as "id" in server tag
*/
class streamiddialog : public QWidget
{
    Q_OBJECT
public:
    /**
    \brief initial the class
    */
    explicit streamiddialog(QWidget *parent = 0);
    /**
    \brief
    \param dialog : window interface as dialog
    */
    QDialog* dialog;
    /**
    \brief
    \param okButton : ok button
    */
    QPushButton* okButton;
    /**
    \brief
    \param idEdit : line edit for "id" edit
    */
    QLineEdit* idEdit;
    /**
    \brief
    \param id : server id
    */
    QString id;
signals:

public slots:
    /**
    \brief get the server id from idEdit
    */
    void getIDSlot();

};

#endif // STREAMIDDIALOG_H
