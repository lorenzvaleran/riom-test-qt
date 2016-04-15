#include "systemtrayicon.h"
#include <QDebug>


SystemTrayIcon::SystemTrayIcon(QObject *parent)
{
    setParent(parent);
    setIcon(QIcon(":/icons/folder-icon1.png"));
    show();

    QObject::connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

SystemTrayIcon::~SystemTrayIcon()
{

}

void SystemTrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::DoubleClick)
        emit doubleClicked();
}

void SystemTrayIcon::msgFileCreated(const QString &filePath)
{
    showMessage("Bonjour", filePath+" créée");
}

void SystemTrayIcon::msgFileModified(const QString &filePath)
{
    showMessage("Bonjour", filePath+" modifié");
}

void SystemTrayIcon::msgFileDeleted(const QString &filePath)
{
    showMessage("Bonjour", filePath+" supprimé");
}
