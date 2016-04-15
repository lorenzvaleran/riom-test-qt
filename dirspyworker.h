#ifndef DIRSPYWORKER_H
#define DIRSPYWORKER_H

#include <QObject>
#include <QTimer>
#include <QFileInfo>
#include <QDateTime>

class file;

class DirSpyWorker : public QObject
{
    Q_OBJECT
public:
    DirSpyWorker(const QString& directory);

public slots:
    void init();
    void checkFiles();
    QHash<QString, QDateTime> getCurrentFileDates();

signals:
    void fileDeleted(const QString& filePath, const QDateTime &dt);
    void fileChanged(const QString& filePath, const QDateTime &dt);
    void fileCreated(const QString& filePath, const QDateTime &dt);

private :
    QString mDir;
    QTimer* mTimer;
    QHash<QString, QDateTime> mFileDates;
};

#endif // DIRSPYWORKER_H
