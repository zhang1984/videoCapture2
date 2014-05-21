#include "openserverdialog.h"

openServerDialog::openServerDialog()
{
    openServer = new QDialog();
    openServer->setWindowTitle("Open Server");
    openServer->setWindowIcon(QIcon(":resource/logo.png"));
    serverEdit = new QLineEdit();
#ifdef _WIN32_
    serverEdit->setInputMask("000.000.000.000");
#elif linux
    serverEdit->setText("Local");
#endif
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    QObject::connect(cancelButton, SIGNAL(clicked()), openServer, SLOT(close()));
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(serverEdit, 0, 0, 1, 2);
    layout->addWidget(okButton, 1, 1);
    layout->addWidget(cancelButton, 1, 2);
    openServer->setLayout(layout);
}
