#ifndef OPENSERVERDIALOG_H
#define OPENSERVERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
/**
\brief
the class defines a open server dialog, to input the server ip address
*/
class openServerDialog
{
public:
    /**
    \brief initial the open server dialog
    */
    openServerDialog();
    /**
    \brief
    \param openServer : a dialog interface
    */
    QDialog* openServer;
    /**
    \brief
    \param serverEdit : a line edit for input the server address
    */
    QLineEdit* serverEdit;
    /**
    \brief
    \param okButton : a button ojbect to accept the input
    */
    QPushButton* okButton;
    /**
    \brief
    \param cancelButton : a button ojbect to close the windows without input
    */
    QPushButton* cancelButton;
};

#endif // OPENSERVERDIALOG_H
