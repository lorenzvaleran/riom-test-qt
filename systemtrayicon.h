#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QWidget>
#include <QSystemTrayIcon>

class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    SystemTrayIcon(QObject *parent=0);
    ~SystemTrayIcon();

signals:
    void doubleClicked();

public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void msgFileCreated (const QString &filePath);
    void msgFileModified(const QString &filePath);
    void msgFileDeleted(const QString &filePath);

};

#endif // SYSTEMTRAYICON_H
