#include "dirspyworker.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>

DirSpyWorker::DirSpyWorker(const QString &directory):
    QObject(NULL),
    mDir(directory),
    mTimer(NULL)
{
}

void DirSpyWorker::init()
{
    mFileDates=getCurrentFileDates();

    qDebug() << "Starting";
    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, &DirSpyWorker::checkFiles);
    mTimer->start(2000);
}

void DirSpyWorker::checkFiles()
{
    qDebug() << "Checking";

    QHash<QString, QDateTime> currentDates;
    currentDates=getCurrentFileDates();

    foreach(const QString& fileName, mFileDates.keys())
    {
        if(!currentDates.contains(fileName))
        {
            //Fichier disparu
            emit fileDeleted(fileName, QDateTime::currentDateTime());
        }
        else if(mFileDates.value(fileName) < currentDates.value(fileName))
        {
            //Dates diff
            emit fileChanged(fileName, currentDates.value(fileName));
        }
    }

    foreach(const QString &fileName, currentDates.keys())
    {
        if(!mFileDates.contains(fileName))
        {
            // Nouveau Fichier
            emit fileCreated(fileName, QDateTime::currentDateTime());
        }
    }

    mFileDates = currentDates;
}

QHash<QString, QDateTime> DirSpyWorker::getCurrentFileDates()
{
    QHash<QString, QDateTime> currentDates;
    QDir dir(mDir);
    foreach(const QFileInfo& info, dir.entryInfoList(QDir::Files))
    {
        currentDates.insert(info.absoluteFilePath(), info.lastModified());
    }
    return currentDates;
}

