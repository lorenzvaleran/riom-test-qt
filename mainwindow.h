#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include "tablewidget.h"
#include "systemtrayicon.h"

namespace Ui {
class MainWindow;
}

class DirSpyWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void getPathSpyDir();
    void spyFolder();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QDateTime dt;

    QThread* thWorker;
    DirSpyWorker* mWordker;
    SystemTrayIcon *sti;
    TableWidget *tab;       
};

#endif // MAINWINDOW_H
