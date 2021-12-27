#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    itemsMenu = menuBar()->addMenu(tr("Items"));
    itemsMenu->addAction(addAction);
    itemsMenu->addAction(removeAction);
    itemsMenu->addAction(clearAction);
    itemsMenu->addAction(selectAllAction);
    itemsMenu->addAction(selectNoneAction);

    stateMenu = menuBar()->addMenu(tr("State"));
    stateMenu->addAction(checkedAction);
    stateMenu->addAction(uncheckedAction);
    stateMenu->addAction(partiallyAction);

}

void MainWindow::createConnection()
{
    connect(newAction, &QAction::triggered, this, &MainWindow::handleNew);
    connect(openAction, &QAction::triggered, this, &MainWindow::handleOpen);
    connect(saveAction, &QAction::triggered, this, &MainWindow::handleSave);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::handleSaveAs);
    connect(exitAction, &QAction::triggered, this, &MainWindow::handleExit);
    connect(addAction, &QAction::triggered, this, &MainWindow::handleAdd);
    connect(removeAction, &QAction::triggered, this, &MainWindow::handleRemove);
    connect(selectAllAction, &QAction::triggered, this, &MainWindow::handleSelectAll);
    connect(selectNoneAction, &QAction::triggered, this, &MainWindow::handleSelectNone);
    connect(checkedAction, &QAction::triggered, this, &MainWindow::handleChecked);
    connect(uncheckedAction, &QAction::triggered, this, &MainWindow::handleUnchecked);
    connect(partiallyAction, &QAction::triggered, this, &MainWindow::handlePartially);
}

void MainWindow::createActions()
{
    newAction = actionFactory(":/files/images/new.png", tr("New"));
    newAction->setShortcut(QKeySequence::New);
    openAction = actionFactory(":/files/images/open.png", tr("Open"));
    openAction->setShortcut(QKeySequence::Open);
    saveAction = actionFactory(":/files/images/save.png", tr("Save"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAsAction = actionFactory(":/files/images/save_as.png", tr("Save As"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    exitAction = actionFactory("", tr("Exit"));

    addAction = new QAction(tr("Add"), this);
    removeAction = new QAction(tr("Remove"), this);
    clearAction = new QAction(tr("Clear"), this);
    selectAllAction = new QAction(tr("Select All"), this);
    exitAction = new QAction(tr("Exit"));

    checkedAction = new QAction(tr("Checked"), this);
    uncheckedAction = new QAction(tr("Unchecked"), this);
    partiallyAction = new QAction(tr("Partially"), this);

    createConnection();
}

QAction* MainWindow::actionFactory(const QString &path, const QString &name)
{
    QAction *action = new QAction(QIcon(path), name, this);
    return action;
}
MainWindow::~MainWindow()
{
}

void MainWindow::handleNew()
{
    qDebug()<< "handleNew clicked...";
}

void MainWindow::handleOpen()
{

}

void MainWindow::handleSave()
{

}

void MainWindow::handleSaveAs()
{

}

void MainWindow::handleExit()
{

}

void MainWindow::handleAdd()
{

}

void MainWindow::handleRemove()
{

}

void MainWindow::handleClear()
{

}

void MainWindow::handleSelectAll()
{

}

void MainWindow::handleSelectNone()
{

}

void MainWindow::handleChecked()
{

}

void MainWindow::handleUnchecked()
{

}

void MainWindow::handlePartially()
{

}



void MainWindow::closeEvent(QCloseEvent *event)
{
}
