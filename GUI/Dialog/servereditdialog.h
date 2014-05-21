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

class serverEditDialog : public QWidget
{
    Q_OBJECT
public:
    explicit serverEditDialog(QString ipAdd, QWidget *parent = 0);
    QDialog* dialog;
    QString ipAdd;
    QLineEdit* projectNameEdit;
    QLineEdit* serverNameEdit;
    QTableWidget* videoCardTable;
    QPushButton* okButton;
    QPushButton* cancelButton;

    QList<cardtype> table2CardList();

    void createTable();
    
signals:

public slots:
    void setOKButtonEnable();

};

#endif // SERVEREDITDIALOG_H
