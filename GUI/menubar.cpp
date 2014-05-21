#include "menubar.h"

menubar::menubar(QWidget *parent) :
    QWidget(parent)
{
    menuBar = new QMenuBar();
    fileMenu = new QMenu("File");
    editMenu = new QMenu("Edit");
    openAct = new QAction("Open Server", this);
    addAct = new QAction("Add...", this);
    addAct->setEnabled(false);
    reloadAct = new QAction("Reload", this);
    closeAct = new QAction("Close", this);
    serverEditAct = new QAction("Server Edit", this);
    //channelEditAct = new QAction("Channel Edit", this);
    streamEditAct = new QAction("Stream Edit", this);
    formatEditAct = new QAction("Format Edit", this);
    copyAct = new QAction("Copy", this);
    copyAct->setEnabled(false);
    pasteAct = new QAction("Paste", this);
    pasteAct->setEnabled(false);
    removeAct = new QAction("Remove", this);
    removeAct->setEnabled(false);
    fileMenu->addAction(openAct);
    fileMenu->addAction(addAct);
    fileMenu->addAction(reloadAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    editMenu->addAction(serverEditAct);
    //editMenu->addAction(channelEditAct);
    editMenu->addAction(streamEditAct);
    editMenu->addAction(formatEditAct);
    editMenu->addSeparator();
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(removeAct);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
}
