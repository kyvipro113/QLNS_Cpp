#include "frameaddtk.h"
#include "ui_frameaddtk.h"
#include <QDebug>

FrameAddTK::FrameAddTK(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddTK)
{
    ui->setupUi(this);
    this->loadData();
}

FrameAddTK::~FrameAddTK()
{
    delete ui;
}

void FrameAddTK::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

QString FrameAddTK::getIDpermission()
{
    QString IDPermission;
    SQLConnection SQL;
    QSqlQuery data = SQL.queryData(QString("Select MaPQ From PhanQuyen Where TenPQ = '%1'").arg(ui->comboPermission->currentText()));
    while(data.next())
    {
        IDPermission = data.value(0).toString();
    }
    SQL.disConnect();
    return IDPermission;
}

void FrameAddTK::loadData()
{
    SQLConnection SQL;

    // Load employee list no have account
    QSqlQuery data_DSNV = SQL.queryData("Select NhanVien.MaNV, NhanVien.TenNV From NhanVien, Login Where NhanVien.MaNV = Login.MaNV and Login.Username is null");
    ui->dataTabDSNV->setRowCount(0);
    int row = 0;
    while(data_DSNV.next())
    {
        ui->dataTabDSNV->insertRow(row);
        for(int col = 0; col < ui->dataTabDSNV->columnCount(); col ++)
            ui->dataTabDSNV->setItem(row, col, new QTableWidgetItem(data_DSNV.value(col).toString()));
        row ++;
    }
    SQL.disConnect();

    // Load DSTK
    row = 0;
    QSqlQuery data_DSTK = SQL.queryData("Select * From Login");
    ui->dataTabDSTK->setRowCount(0);
    while(data_DSTK.next())
    {
        ui->dataTabDSTK->insertRow(row);
        for(int col = 0; col < ui->dataTabDSTK->columnCount(); col ++)
            ui->dataTabDSTK->setItem(row, col, new QTableWidgetItem(data_DSTK.value(col).toString()));
        row ++;
    }
    SQL.disConnect();

    // Load Permission
    ui->comboPermission->clear();
    QSqlQuery data_Permission = SQL.queryData("Select TenPQ From PhanQuyen");
    while(data_Permission.next())
    {
        ui->comboPermission->addItem(data_Permission.value(0).toString());
    }
    SQL.disConnect();
    ui->lbMaNV->setText("");
    ui->lbTenNV->setText("");
    ui->txtUserName->setText("");
    ui->txtPassword->setText("");
}

void FrameAddTK::on_btFix_clicked()
{
    if(ui->lbMaNV->text() == "")
        this->alert("Cảnh báo", "Chưa chọn nhân viên");
    else
    {
        try
        {
            QString IDPermission = getIDpermission();
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Update Login Set Username = '%1', Password = '%2', MaPQ = '%3' Where MaNV = '%4'")
                                  .arg(ui->txtUserName->text(), ui->txtPassword->text(), IDPermission, ui->lbMaNV->text()));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiện thành công");
        }
        catch(QString err)
        {
            err = "Thao tác thực hiện thất bại!";
            this->alert("Cảnh báo", err);
        }
    }
    this->loadData();
}

void FrameAddTK::on_btDel_clicked()
{
    if(ui->lbMaNV->text() == "")
        this->alert("Cảnh báo", "Chưa chọn nhân viên!");
    else
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Update Login Set Username = null, Password = null, MaPQ = null Where MaNV = '%1'").arg(ui->lbMaNV->text()));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiện thành công");
        }
        catch(QString err)
        {
            err = "Thao tác thực hiện thất bại!";
            this->alert("Cảnh báo", err);
        }
    }
    this->loadData();
}

void FrameAddTK::on_btClear_clicked()
{
    ui->lbMaNV->setText("");
    ui->lbTenNV->setText("");
    ui->txtUserName->setText("");
    ui->txtPassword->setText("");
}

void FrameAddTK::on_dataTabDSNV_cellClicked(int row)
{
    ui->lbMaNV->setText(ui->dataTabDSNV->item(row, 0)->text());
    ui->lbTenNV->setText(ui->dataTabDSNV->item(row, 1)->text());
    ui->txtUserName->setText("");
    ui->txtPassword->setText("");
}

void FrameAddTK::on_dataTabDSTK_cellClicked(int row)
{
    SQLConnection SQL;
    ui->lbMaNV->setText(ui->dataTabDSTK->item(row, 0)->text());
    QSqlQuery data_EmpName = SQL.queryData(QString("Select TenNV From NhanVien Where MaNV = '%1'").arg(ui->dataTabDSTK->item(row, 0)->text()));
    while(data_EmpName.next())
        ui->lbTenNV->setText(data_EmpName.value(0).toString());
    SQL.disConnect();
    ui->txtUserName->setText(ui->dataTabDSTK->item(row, 1)->text());
    ui->txtPassword->setText(ui->dataTabDSTK->item(row, 2)->text());
    if(ui->dataTabDSTK->item(row, 3)->text() != NULL)
    {
        QSqlQuery data_NamePermiss = SQL.queryData(QString("Select TenPQ From PhanQuyen Where MaPQ = '%1'").arg(ui->dataTabDSTK->item(row, 3)->text()));
        while(data_NamePermiss.next())
        {
            ui->comboPermission->setCurrentText(data_NamePermiss.value(0).toString());
        }
        SQL.disConnect();
    }

}
