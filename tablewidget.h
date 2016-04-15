#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QMap>

namespace Ui {
class TableWidget;
}

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent=0);
    ~TableWidget();

private:
    Ui::TableWidget *ui;
    QMap <QString, int> mapPosFic;

private slots:
    void clearTable();

public slots:
    void addLigne(const QString &nameFile, const QDateTime &dateTime);
    void showTable();

};

#endif // TABLEWIDGET_H
