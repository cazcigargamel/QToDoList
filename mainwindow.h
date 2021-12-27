#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDataStream>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ///File Actions
    QAction *newAction = nullptr;
    QAction *openAction = nullptr;
    QAction *saveAction = nullptr;
    QAction *saveAsAction = nullptr;
    QAction *exitAction = nullptr;
    ///Items Actions
    QAction *addAction = nullptr;
    QAction *removeAction =nullptr;
    QAction *clearAction = nullptr;
    QAction *selectAllAction = nullptr;
    QAction *selectNoneAction = nullptr;
    ///State Actions
    QAction *checkedAction = nullptr;
    QAction *uncheckedAction = nullptr;
    QAction *partiallyAction = nullptr;

    QMenu *fileMenu = nullptr;
    QMenu *itemsMenu = nullptr;
    QMenu *stateMenu = nullptr;

    void createActions();
    QAction *actionFactory(const QString &path, const QString &name);
    void createConnection();

    QString m_filename;
    bool m_changed;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleNew();
    void handleOpen();
    void handleSave();
    void handleSaveAs();
    void handleExit();

    void handleAdd();
    void handleRemove();
    void handleClear();
    void handleSelectAll();
    void handleSelectNone();

    void handleChecked();
    void handleUnchecked();
    void handlePartially();


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
