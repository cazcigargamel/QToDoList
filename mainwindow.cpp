#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>

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

    listWidget = new QListWidget;
    listWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    setCentralWidget(listWidget);
    create();

    QToolBar *fileToolBar = addToolBar("File");
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);
    fileToolBar->addSeparator();
    fileToolBar->addAction(addAction);
    fileToolBar->addAction(exitAction);
    fileToolBar->addSeparator();
    fileToolBar->addAction(checkedAction);
    fileToolBar->addAction(partiallyAction);
    fileToolBar->addAction(uncheckedAction);
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

void MainWindow::create()
{
    m_changed = false;
    m_filename.clear();
    listWidget->clear();
}

void MainWindow::open(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QDataStream stream(&file);
    int count;
    stream >> count;

    for(int i = 0; i < count ; ++i)
    {
        int state;
        QString name;
        stream >> state;
        stream >> name;
        Qt::CheckState checkstate = static_cast<Qt::CheckState>(state);
        createItem(checkstate, name);
    }
    file.close();
    m_filename = path;
    m_changed = false;
}

void MainWindow::save(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QDataStream stream(&file);
    stream << listWidget->count();
    for(int i = 0; i < listWidget->count(); ++i)
    {
       QListWidgetItem *item = listWidget->item(i);
       int state = static_cast<int>(item->checkState());
       stream << state;
       stream << item->text();
    }
    file.close();
    m_filename = path;
    m_changed = false;
}

void MainWindow::checkSave()
{
    if(!m_changed) return;
    QMessageBox::StandardButton btn = QMessageBox::question(this, "Save File?", "Do you want to save your changes?");
    if(btn == QMessageBox::StandardButton::Yes) save(m_filename);
}

void MainWindow::checkItem(Qt::CheckState state, QString name)
{

}

void MainWindow::createItem(Qt::CheckState state, QString name)
{
    QListWidgetItem *item = new QListWidgetItem("name", listWidget);
    item->setCheckState(state);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable |
                   Qt::ItemFlag::ItemIsUserTristate |
                   Qt::ItemFlag::ItemIsUserCheckable |
                   Qt::ItemFlag::ItemIsSelectable);
    listWidget->addItem(item);
}


void MainWindow::createActions()
{
    newAction = actionFactory(":/files/images/new.png", tr("&New"));
    newAction->setShortcut(QKeySequence::New);
    openAction = actionFactory(":/files/images/open.png", tr("&Open"));
    openAction->setShortcut(QKeySequence::Open);
    saveAction = actionFactory(":/files/images/save.png", tr("&Save"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAsAction = actionFactory(":/files/images/save_as.png", tr("Sa&ve As"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    exitAction = actionFactory("", tr("Exit"));

    addAction = actionFactory(":/files/images/add.png", tr("&Add"));
    addAction->setShortcut(QKeySequence(tr("Ctrl+A")));
    removeAction = actionFactory(":/files/images/delete.png", tr("&Delete"));
    removeAction->setShortcut(QKeySequence(tr("Ctrl+D")));
    clearAction = new QAction(tr("Clear"), this);
    selectAllAction = new QAction(tr("Select All"), this);
    exitAction = actionFactory(":/files/images/cancel.png", tr("&Exit"));

    checkedAction = actionFactory(":/files/images/pencil_add.png", tr("&Checked"));
    uncheckedAction = actionFactory(":/files/images/pencil_go.png", tr("&Unchecked"));
    partiallyAction = actionFactory(":/files/images/pencil_delete.png", tr("Partia&lly"));

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
    checkSave();
    create();
}

void MainWindow::handleOpen()
{
    checkSave();
    QString path = QFileDialog::getOpenFileName(this, "Open", "", "To-Do (*.td)");
    if(!path.isEmpty()) return;
    open(path);
}

void MainWindow::handleSave()
{
    if(m_filename.isEmpty())
    {
        handleSaveAs();
        return;
    }
    save(m_filename);
}

void MainWindow::handleSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this, "Open", "To-Do (*.td)");
    if(path.isEmpty()) return;
    save(path);
}

void MainWindow::handleExit()
{
    close();
}

void MainWindow::handleAdd()
{
    createItem(Qt::CheckState::Unchecked, "New Item");
}

void MainWindow::handleRemove()
{
    QList<QListWidgetItem*> list = listWidget->selectedItems();
    foreach(QListWidgetItem* item, list)
    {
        delete listWidget->takeItem(listWidget->row(item));
    }
    m_changed = true;
}

void MainWindow::handleClear()
{
    listWidget->clear();
    m_changed = true;
}

void MainWindow::handleSelectAll()
{
    listWidget->selectAll();
}

void MainWindow::handleSelectNone()
{
    listWidget->clearSelection();
}

void MainWindow::handleChecked()
{
    QList<QListWidgetItem*> list = listWidget->selectedItems();
    foreach(QListWidgetItem *item, list)
    {
        item->setCheckState(Qt::CheckState::Checked);
    }
    m_changed = true;
}

void MainWindow::handleUnchecked()
{
    QList<QListWidgetItem*> list = listWidget->selectedItems();
    foreach(QListWidgetItem *item, list)
    {
        item->setCheckState(Qt::CheckState::Unchecked);
    }
    m_changed = true;
}

void MainWindow::handlePartially()
{
    QList<QListWidgetItem*> list = listWidget->selectedItems();
    foreach(QListWidgetItem *item, list)
    {
        item->setCheckState(Qt::CheckState::PartiallyChecked);
    }
    m_changed = true;
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
