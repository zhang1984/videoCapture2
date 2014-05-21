#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class menubar : public QWidget
{
    Q_OBJECT
public:
    explicit menubar(QWidget *parent = 0);
    QMenuBar* menuBar;
    QMenu* fileMenu;
    QMenu* editMenu;
    QAction* addAct;
    QAction* openAct;
    QAction* reloadAct;
    QAction* closeAct;
    QAction* serverEditAct;
    //QAction* channelEditAct;
    QAction* streamEditAct;
    QAction* formatEditAct;
    QAction* copyAct;
    QAction* pasteAct;
    QAction* removeAct;
signals:

public slots:

};

#endif // MENUBAR_H
