#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
/**
\brief define the menubar in mainwindow class
*/
class menubar : public QWidget
{
    Q_OBJECT
public:
    /**
    \brief initial the menubar
    */
    explicit menubar(QWidget *parent = 0);
    /**
    \brief
    \param menuBar : menu bar object
    */
    QMenuBar* menuBar;
    /**
    \brief
    \param fileMenu : a "File" menu container
    */
    QMenu* fileMenu;
    /**
    \brief
    \param editMenu : a "Edit" menu container
    */
    QMenu* editMenu;
    /**
    \brief
    \param addAct : "Add..." action
    */
    QAction* addAct;
    /**
    \brief
    \param openAct : "Open" action
    */
    QAction* openAct;
    /**
    \brief
    \param reloadAct : "Reload" action
    */
    QAction* reloadAct;
    /**
    \brief
    \param closeAct : "Close" action
    */
    QAction* closeAct;
    /**
    \brief
    \param serverEditAct : "Server Edit" action
    */
    QAction* serverEditAct;
    /**
    \brief
    \param streamEditAct : "Stream Edit" action
    */
    QAction* streamEditAct;
    /**
    \brief
    \param formatEditAct : "Format Edit" action
    */
    QAction* formatEditAct;
    /**
    \brief
    \param copyAct : "Copy" action
    */
    QAction* copyAct;
    /**
    \brief
    \param pasteAct : "Paste" action
    */
    QAction* pasteAct;
    /**
    \brief
    \param removeAct : "Remove" action
    */
    QAction* removeAct;
signals:

public slots:

};

#endif // MENUBAR_H
