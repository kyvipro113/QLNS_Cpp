#include "framepb.h"
#include "ui_framepb.h"

FramePB::FramePB(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FramePB)
{
    ui->setupUi(this);
    this->loadData();
}

FramePB::~FramePB()
{
    delete ui;
}

void FramePB::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void FramePB::loadData()
{
    SQLConnection SQL;
    QSqlQuery data = SQL.queryData("Select * From PhongBan");
    ui->dataTab->setRowCount(0);
    int row = 0;
    int column = ui->dataTab->columnCount();
    while(data.next())
    {
        ui->dataTab->insertRow(row);
        for(int column_number = 0; column_number < column; column_number ++)
        {
            ui->dataTab->setItem(row, column_number, new QTableWidgetItem(data.value(column_number).toString()));
        }
        row ++;
    }
    SQL.disConnect();
    for(int row_number = 0; row_number <ui->dataTab->rowCount(); row_number++)
    {
        QString itemID = ui->dataTab->item(row_number, 0)->text();
        QSqlQuery data_soluongNV = SQL.queryData(QString("Select COUNT(*) From NhanVien, PhongBan Where NhanVien.MaPB = PhongBan.MaPB and PhongBan.MaPB = '%1'").arg(itemID));
        while(data_soluongNV.next())
            ui->dataTab->setItem(row_number, 2, new QTableWidgetItem(data_soluongNV.value(0).toString()));
        SQL.disConnect();
    }
    ui->txtMaPB->setText("");
    ui->txtTenPB->setText("");
    ui->lbSoNV->setText("0");
}

bool FramePB::checkEmpty()
{
    if(ui->txtMaPB->text() == "" || ui->txtTenPB->text() == "")
        return false;
    return true;
}

void FramePB::on_btAdd_clicked()
{
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Insert Into PhongBan Values('%1', '%2')").arg(ui->txtMaPB->text(), ui->txtTenPB->text()));
            SQL.disConnect();
            //Alert
            this->alert("Thông báo","Thao tác thực hiện thành công!");
            this->loadData();
        }
        catch(const QString *err)
        {
            //err = "";
            this->alert("Cảnh báo", "Thao tác thực hiện thất bại!");
        }
    }
    else
        this->alert("Cảnh báo", "Không được để trống các trường!");
}

void FramePB::on_btFix_clicked()
{
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Update PhongBan Set TenPb = '%1' Where MaPB = '%2'").arg(ui->txtTenPB->text(), ui->txtMaPB->text()));

            SQL.disConnect();
            //Alert
            this->alert("Thông báo", "Thao tác thực hiện thành công!");

        }
        catch(const QString err)
        {
            this->alert("Cảnh báo", "Thao tác thực hiện thất bại");
        }
    }
    else
        this->alert("Cảnh báo", "Chưa chọn phòng ban cần sửa!");
    this->loadData();

}

void FramePB::on_btDel_clicked()
{
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Delete PhongBan Where MaPB = '%1'").arg(ui->txtMaPB->text()));
            SQL.disConnect();
            //Alert
            this->alert("Thông báo", "Thao tác thực hiện thành công!");

        }
        catch(const QString err)
        {
            this->alert("Cảnh báo", "Thao tác thực hiện thất bại!");
        }
    }
    else
        this->alert("Cảnh báo", "Chưa chọn phòng ban cần xóa!");
    this->loadData();
}

void FramePB::on_btClear_clicked()
{
    ui->txtMaPB->setText("");
    ui->txtTenPB->setText("");
    ui->lbSoNV->setText("0");
}

void FramePB::on_dataTab_cellClicked(int row)
{
    ui->txtMaPB->setText(ui->dataTab->item(row, 0)->text());
    ui->txtTenPB->setText(ui->dataTab->item(row, 1)->text());
    ui->lbSoNV->setText(ui->dataTab->item(row, 2)->text());
}
