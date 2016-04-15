#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QDebug>
#include <QScrollBar>


TableWidget::TableWidget(QWidget *parent) :
    ui(new Ui::TableWidget)
{    
    ui->setupUi(this);

    setParent(parent);
    setWindowTitle("Journal de modification");
    setWindowIcon(QIcon(":/icons/folder-icon1.png"));
    setFocus();

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(clearTable()));
}

TableWidget::~TableWidget()
{
}

void TableWidget::addLigne(const QString &nameFile, const QDateTime &dateTime)
{
    qDebug() << "Add ligne demandée";

    QMap<QString, int>::const_iterator it=mapPosFic.find(nameFile);

    if(it==mapPosFic.end())
    {
        int pos=mapPosFic.size();

        ui->tableWidget->setItem(pos, 0, new QTableWidgetItem(nameFile));
        ui->tableWidget->setItem(pos, 1, new QTableWidgetItem(dateTime.toString()));

        mapPosFic[nameFile]=pos;
    }
    else
    {
        ui->tableWidget->item(it.value(), 1)->setText(dateTime.toString());
    }
}

void TableWidget::showTable()
{
    setVisible(true);
}

void TableWidget::clearTable()
{
    ui->tableWidget->clearContents();
    mapPosFic.clear();
}
