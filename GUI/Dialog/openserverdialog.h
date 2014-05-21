#ifndef OPENSERVERDIALOG_H
#define OPENSERVERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>

class openServerDialog
{
public:
    openServerDialog();
    QDialog* openServer;
    QLineEdit* serverEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;
};

#endif // OPENSERVERDIALOG_H
