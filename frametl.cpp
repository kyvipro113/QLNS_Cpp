#include "frametl.h"
#include "ui_frametl.h"
#include <QDebug>

FrameTL::FrameTL(QWidget *parent, QString monthTL, QString yearTL, QString dateTL) :
    QFrame(parent),
    ui(new Ui::FrameTL)
{
    ui->setupUi(this);
    this->monthTL = monthTL;
    this->yearTL = yearTL;
    this->dateTL = dateTL;
    this->loadData();
}

FrameTL::~FrameTL()
{
    delete ui;
}

void FrameTL::loadData()
{
    SQLConnection SQL;
    QSqlQuery data = SQL.queryData("Select * From Luong");
    ui->dataTab->setRowCount(0);
    int row = 0;
    while(data.next())
    {
        ui->dataTab->insertRow(row);
        for(int col = 0; col < ui->dataTab->columnCount(); col ++)
        {
            ui->dataTab->setItem(row, col, new QTableWidgetItem(data.value(col).toString()));
        }
        row ++;
    }
    SQL.disConnect();

    for(int row_number = 0; row_number < ui->dataTab->rowCount(); row_number ++)
    {
        QSqlQuery data_NV = SQL.queryData(QString("Select TenNV From NhanVien Where MaNV = '%1'").arg(ui->dataTab->item(row_number, 0)->text()));
        while(data_NV.next())
            ui->dataTab->setItem(row_number, 0, new QTableWidgetItem(data_NV.value(0).toString()));
        SQL.disConnect();
    }
}

void FrameTL::on_btTinhLuong_clicked()
{
    try
    {
        SQLConnection SQL;
        QStringList listIDNV;
        QSqlQuery data_IDNV = SQL.queryData("Select MaNV From NhanVien");
        while(data_IDNV.next())
            listIDNV.append(data_IDNV.value(0).toString());
        SQL.disConnect();
         qDebug() << listIDNV;
         for(const QString &itemID : listIDNV)
            SQL.queryDataNoReturn(QString("Exec tinhLuong @MaNV = '%1', @thang = '%2'").arg(itemID, this->monthTL));
         SQL.disConnect();

    }
    catch(QString err)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Cảnh báo");
        msgBox.setText("Không tìm thấy");
        msgBox.exec();
    }
    this->loadData();
}

void FrameTL::on_btView_clicked()
{
    try
    {
        SQLConnection SQL;
        QSqlQuery data = SQL.queryData(QString("Select *From Luong Where MONTH(Thang) = '%1' and YEAR(Thang) = '%2'").arg(this->monthTL, this->yearTL));
        ui->dataTab->setRowCount(0);
        int row = 0;
        while(data.next())
        {
            ui->dataTab->insertRow(row);
            for(int col = 0; col < ui->dataTab->columnCount(); col ++)
                ui->dataTab->setItem(row, col, new QTableWidgetItem(data.value(col).toString()));
            row ++;
        }
        SQL.disConnect();

        for(int row_number = 0; row_number < ui->dataTab->rowCount(); row_number ++)
        {
            QSqlQuery data_NV = SQL.queryData(QString("Select TenNV From NhanVien Where MaNV = '%1'").arg(ui->dataTab->item(row_number, 0)->text()));
            while(data_NV.next())
                ui->dataTab->setItem(row_number, 0, new QTableWidgetItem(data_NV.value(0).toString()));
            SQL.disConnect();
        }
    }
    catch(QString err)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Cảnh báo");
        msgBox.setText("Không tìm thấy");
        msgBox.exec();
    }
}

void FrameTL::on_btLoad_clicked()
{
    this->loadData();
}

void FrameTL::on_deMonth_dateChanged(const QDate &date)
{
    QString day, ch = "/";
    this->yearTL = QString::number(date.year());
    this->monthTL = QString::number(date.month());
    day = QString::number(date.day());
    this->dateTL = this->yearTL + ch + this->monthTL + ch + day;
}
