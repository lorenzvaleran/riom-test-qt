#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <QDebug>
#include <dirspyworker.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    thWorker(NULL),
    mWordker(NULL),
    sti(new SystemTrayIcon()),
    tab(new TableWidget())
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/folder-icon1.png"));

    QObject::connect(ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(getPathSpyDir()));
    QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(spyFolder()));
    QObject::connect(sti, &SystemTrayIcon::doubleClicked, tab, &TableWidget::showTable);
}

MainWindow::~MainWindow()
{
    thWorker->terminate();
    thWorker->wait();

    delete thWorker;
    delete mWordker;
    delete ui;
    delete tab;
    delete sti;

}

void MainWindow::getPathSpyDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    qDebug() << dir;

    if(!dir.isEmpty())
        ui->lineEdit->setText(dir);
}

void MainWindow::spyFolder()
{
    if(ui->lineEdit->text()=="")
    {
        QMessageBox msgBox;
        msgBox.setText("No directory selected.");
        msgBox.exec();
    }
    else
    {
        if(thWorker)
        {
            thWorker->terminate();
            thWorker->wait();
            delete thWorker;
        }

        thWorker = new QThread(this);
        delete mWordker;
        mWordker = new DirSpyWorker(ui->lineEdit->text());
        mWordker->moveToThread(thWorker);
        connect(thWorker, &QThread::started, mWordker, &DirSpyWorker::init);
        thWorker->start();

        connect(mWordker, &DirSpyWorker::fileDeleted, sti, &SystemTrayIcon::msgFileDeleted);
        connect(mWordker, &DirSpyWorker::fileCreated, sti, &SystemTrayIcon::msgFileCreated);
        connect(mWordker, &DirSpyWorker::fileChanged, sti, &SystemTrayIcon::msgFileModified);

        connect(mWordker, SIGNAL(fileCreated(QString, QDateTime)), tab, SLOT(addLigne(QString, QDateTime)));
        connect(mWordker, SIGNAL(fileChanged(QString, QDateTime)), tab, SLOT(addLigne(QString, QDateTime)));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    tab->hide();
    sti->setVisible(false);
}

