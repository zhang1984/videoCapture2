#ifndef SERVEREDITDIALOG_H
#define SERVEREDITDIALOG_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QGridLayout>
#include <config/cardtype.h>

#include <QDebug>
/**
\brief
the class defines a server edit dialog, set the parameters of the server, like the name of the server, the name of the project in the server, the video cards' names of the server and the channel number under the video card
*/
class serverEditDialog : public QWidget
{
    Q_OBJECT
public:
    /**
    \brief initial the class
    */
    explicit serverEditDialog(QString ipAdd, QWidget *parent = 0);
    /**
    \brief
    \param dialog : dialog interface
    */
    QDialog* dialog;
    /**
    \brief
    \param ipAdd : the ip address of the server
    */
    QString ipAdd;
    /**
    \brief
    \param projectNameEdit : a line edit for project name
    */
    QLineEdit* projectNameEdit;
    /**
    \brief
    \param serverNameEdit : a line edit for server name
    */
    QLineEdit* serverNameEdit;
    /**
    \brief
    \param videoCardTable : a table widget for output the components
    */
    QTableWidget* videoCardTable;
    /**
    \brief
    \param okButton : accept the configuration button
    */
    QPushButton* okButton;
    /**
    \brief
    \param cancelButton : close the window without acception
    */
    QPushButton* cancelButton;

    /**
    \brief set predefined video card information in the table
    */
    QList<cardtype> table2CardList();
    /**
    \brief create the table component in initial phase
    */
    void createTable();
    
signals:

public slots:
    /**
    \brief change the okButton status, if the configuration data changed
    */
    void setOKButtonEnable();
};

#endif // SERVEREDITDIALOG_H
