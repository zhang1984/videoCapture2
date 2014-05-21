#include "streamiddialog.h"

streamiddialog::streamiddialog(QWidget *parent) :
    QWidget(parent)
{
    dialog = new QDialog();
    dialog->setWindowTitle("Server id?");
    dialog->setWindowIcon(QIcon(":resource/logo.png"));
    idEdit = new QLineEdit();
    okButton = new QPushButton("OK");
    connect(okButton, SIGNAL(clicked()), this, SLOT(getIDSlot()));

    QLabel* _l = new QLabel();
    _l->setText("Server_ID: ");
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(_l, 0, 0);
    layout->addWidget(idEdit, 0, 1);
    layout->addWidget(okButton,1,1);

    dialog->setLayout(layout);
}

void streamiddialog::getIDSlot()
{
    id = idEdit->text();
    if(!id.isEmpty())
    {
        dialog->close();
    }
}
