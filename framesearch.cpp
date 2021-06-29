#include "framesearch.h"
#include "ui_framesearch.h"

FrameSearch::FrameSearch(QWidget *parent, int statusRadioBT) :
    QFrame(parent),
    ui(new Ui::FrameSearch)
{
    ui->setupUi(this);
    this->statusRadioBT = statusRadioBT;
}

FrameSearch::~FrameSearch()
{
    delete ui;
}

void FrameSearch::loadData(QSqlQuery data)
{
    int row = 0;
    ui->dataTab->setRowCount(0);
    while(data.next())
    {
        ui->dataTab->insertRow(row);
        for(int col = 0; col < ui->dataTab->columnCount(); col ++)
            ui->dataTab->setItem(row, col, new QTableWidgetItem(data.value(col).toString()));
        row ++;
    }
}

void FrameSearch::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void FrameSearch::on_radioBTName_toggled(bool checked)
{
    if(checked)
        this->statusRadioBT = 1;
}

void FrameSearch::on_radioBTID_toggled(bool checked)
{
    if(checked)
        this->statusRadioBT = 0;
}

void FrameSearch::on_btSearch_clicked()
{
    SQLConnection SQL;
    QSqlQuery data;
    try
    {
        if(statusRadioBT == 0)
        {
            data = SQL.queryData(QString("Select MaNV, TenNV, MaPB, MaCV, GioiTinh, NgaySinh, SDT, CMT From NhanVien Where MaNV Like N'%%1%'").arg(ui->txtSearch->text()));
            this->loadData(data);
            data = SQL.queryData(QString("Select TenPB From PhongBan Where MaPB = '%1'").arg(ui->dataTab->item(0, 2)->text()));
            while(data.next())
                ui->dataTab->setItem(0, 2, new QTableWidgetItem(data.value(0).toString()));
            data = SQL.queryData(QString("Select TenCV From ChucVu Where MaCV = '%1'").arg(ui->dataTab->item(0, 3)->text()));
            while(data.next())
                ui->dataTab->setItem(0, 3, new QTableWidgetItem(data.value(0).toString()));
            SQL.disConnect();
        }
        else if(statusRadioBT == 1)
        {
            data = SQL.queryData(QString("Select MaNV, TenNV, MaPB, MaCV, GioiTinh, NgaySinh, SDT, CMT From NhanVien Where TenNV Like N'%%1%'").arg(ui->txtSearch->text()));
            this->loadData(data);
            data = SQL.queryData(QString("Select TenPB From PhongBan Where MaPB = '%1'").arg(ui->dataTab->item(0, 2)->text()));
            while(data.next())
                ui->dataTab->setItem(0, 2, new QTableWidgetItem(data.value(0).toString()));
            data = SQL.queryData(QString("Select TenCV From ChucVu Where MaCV = '%1'").arg(ui->dataTab->item(0, 3)->text()));
            while(data.next())
                ui->dataTab->setItem(0, 3, new QTableWidgetItem(data.value(0).toString()));
            SQL.disConnect();
        }
        else
            this->alert("Cảnh báo", "Chưa chọn danh mục tìm kiếm!");
    }
    catch (...)
    {
        this->alert("Cảnh báo", "Thao tác thực hiện thất bại");
    }
}
