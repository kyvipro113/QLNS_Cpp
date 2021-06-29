#include "framekt.h"
#include "ui_framekt.h"
#include <QDebug>

FrameKT::FrameKT(QWidget *parent, QString currentDate, int statusRadioBT, QString IDNV) :
    QFrame(parent),
    ui(new Ui::FrameKT)
{
    ui->setupUi(this);
    this->currentDate = currentDate;
    this->statusRadioBT = statusRadioBT;
    this->IDNV = IDNV;
    this->loadData();
}

FrameKT::~FrameKT()
{
    delete ui;
}

void FrameKT::loadData()
{
    SQLConnection SQL;
    int row = 0;
    QSqlQuery data_NV = SQL.queryData("Select MaNV, TenNV From NhanVien");
    ui->dataTabNhanVien->setRowCount(0);
    while(data_NV.next())
    {
        ui->dataTabNhanVien->insertRow(row);
        for(int col = 0; col < ui->dataTabNhanVien->columnCount(); col ++)
            ui->dataTabNhanVien->setItem(row, col, new QTableWidgetItem(data_NV.value(col).toString()));
        row ++;
    }
    SQL.disConnect();
    // Load DSNV

    row = 0;
    QSqlQuery data_KT = SQL.queryData("SElect * From KhenThuong");
    ui->dataTabKhenThuong->setRowCount(0);
    while(data_KT.next())
    {
        ui->dataTabKhenThuong->insertRow(row);
        for(int col = 0; col < ui->dataTabKhenThuong->columnCount(); col ++)
            ui->dataTabKhenThuong->setItem(row, col, new QTableWidgetItem(data_KT.value(col).toString()));
        row ++;
    }
    SQL.disConnect();
    // Load DSKT

    row = 0;
    QSqlQuery data_KL = SQL.queryData("SElect * From KyLuat");
    ui->dataTabKyLuat->setRowCount(0);
    while(data_KL.next())
    {
        ui->dataTabKyLuat->insertRow(row);
        for(int col = 0; col < ui->dataTabKyLuat->columnCount(); col ++)
            ui->dataTabKyLuat->setItem(row, col, new QTableWidgetItem(data_KL.value(col).toString()));
        row ++;
    }
    SQL.disConnect();
}

bool FrameKT::checkEmpty()
{
    if(ui->lbTenNV->text() == "" || ui->txtLyDo->toPlainText() == "" || ui->txtSoTien->text() == "" || this->statusRadioBT == 2)
        return false;
    return true;
}

void FrameKT::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void FrameKT::cleanText()
{
    ui->deDate->setDate(QDate(2000, 1, 1));
    ui->lbTenNV->setText("");
    ui->txtLyDo->setText("");
    ui->txtSoTien->setText("");
    ui->radioBTKhenThuong->setChecked(false);
    ui->radioBTKyLuat->setCheckable(false);
}

void FrameKT::on_btAdd_clicked()
{
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            if(statusRadioBT == 0)
                SQL.queryDataNoReturn(QString("Insert Into KhenThuong Values ('%1', N'%2', '%3', '%4')").arg(this->IDNV, ui->txtLyDo->toPlainText(), ui->txtSoTien->text(), this->currentDate));
            if(statusRadioBT == 1)
                SQL.queryDataNoReturn(QString("Insert Into KyLuat Values ('%1', N'%2', '%3', '%4')").arg(this->IDNV, ui->txtLyDo->toPlainText(), ui->txtSoTien->text(), this->currentDate));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiện thành công");
        }
        catch(const QString err)
        {
            this->alert("Cảnh báo", err);
        }
    }
    else
        this->alert("Cảnh báo", "Không được để trống các trường");
    this->loadData();
}

void FrameKT::on_btDel_clicked()
{
    if(ui->lbTenNV->text() == "")
        this->alert("Cảnh báo", "Chưa chọn nhân viên cần xóa");
    else
    {
        SQLConnection SQL;
        try
        {
            if(statusRadioBT == 0)
                SQL.queryDataNoReturn(QString("Delete KhenThuong Where MaNV = '%1'").arg(this->IDNV));
            if(statusRadioBT == 1)
                SQL.queryDataNoReturn(QString("Delete KyLuat Where MaNV = '%1'").arg(this->IDNV));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiện thành công!");
        }
        catch (const QString err)
        {
            this->alert("Cảnh báo", err);
        }
    }
    this->loadData();
    this->cleanText();
}

void FrameKT::on_btClear_clicked()
{
    this->cleanText();
}

void FrameKT::on_deDate_dateChanged(const QDate &date)
{
    QString year, month, day, ch = "/";
    year = QString::number(date.year());
    month = QString::number(date.month());
    day = QString::number(date.day());
    this->currentDate = year + ch + month + ch + day;
    //qDebug() << this->currentDate;
}

void FrameKT::on_radioBTKhenThuong_toggled(bool checked)
{
    if(checked)
        this->statusRadioBT = 0;
}

void FrameKT::on_radioBTKyLuat_toggled(bool checked)
{
    if(checked)
        this->statusRadioBT = 1;
}

void FrameKT::on_dataTabNhanVien_cellClicked(int row)
{
    this->IDNV = ui->dataTabNhanVien->item(row, 0)->text();
    ui->lbTenNV->setText(ui->dataTabNhanVien->item(row, 1)->text());
}

void FrameKT::on_dataTabKhenThuong_cellClicked(int row)
{
    ui->lbTenNV->setText(ui->dataTabKhenThuong->item(row, 0)->text());
    SQLConnection SQL;
    QSqlQuery data_NV = SQL.queryData(QString("Select TenNV From NhanVien Where MaNV = '%1'").arg(ui->dataTabKhenThuong->item(row, 0)->text()));
    while(data_NV.next())
        ui->lbTenNV->setText(data_NV.value(0).toString());
    SQL.disConnect();
    ui->radioBTKhenThuong->setChecked(true);
    ui->txtLyDo->setText(ui->dataTabKhenThuong->item(row, 1)->text());
    ui->txtSoTien->setText(ui->dataTabKhenThuong->item(row, 2)->text());
    QString cDate = ui->dataTabKhenThuong->item(row, 3)->text();
    QDate date = QDate(cDate.split(QLatin1Char('-'))[0].toInt(), cDate.split(QLatin1Char('-'))[1].toInt(), cDate.split(QLatin1Char('-'))[2].toInt());
    ui->deDate->setDate(date);
}

void FrameKT::on_dataTabKyLuat_cellClicked(int row)
{
    ui->lbTenNV->setText(ui->dataTabKyLuat->item(row, 0)->text());
    SQLConnection SQL;
    QSqlQuery data_NV = SQL.queryData(QString("Select TenNV From NhanVien Where MaNV = '%1'").arg(ui->dataTabKyLuat->item(row, 0)->text()));
    while(data_NV.next())
        ui->lbTenNV->setText(data_NV.value(0).toString());
    SQL.disConnect();
    ui->radioBTKyLuat->setChecked(true);
    ui->txtLyDo->setText(ui->dataTabKyLuat->item(row, 1)->text());
    ui->txtSoTien->setText(ui->dataTabKyLuat->item(row, 2)->text());
    QString cDate = ui->dataTabKyLuat->item(row, 3)->text();
    QDate date = QDate(cDate.split(QLatin1Char('-'))[0].toInt(), cDate.split(QLatin1Char('-'))[1].toInt(), cDate.split(QLatin1Char('-'))[2].toInt());
    ui->deDate->setDate(date);
}
