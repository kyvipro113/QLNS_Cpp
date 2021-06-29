#include "framecv.h"
#include "ui_framecv.h"
#include <QMessageBox>

FrameCV::FrameCV(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameCV)
{
    ui->setupUi(this);
    this->loadData();
}

FrameCV::~FrameCV()
{
    delete ui;
}

void FrameCV::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

bool FrameCV::checkEmpty()
{
    if(ui->txtMaCV->text() == "" || ui->txtTenCV->text() == "")
        return false;
    return true;
}

void FrameCV::loadData()
{
    SQLConnection SQL;
    QSqlQuery data = SQL.queryData("Select * From ChucVu");
    int row = 0;
    ui->dataTab->setRowCount(0);
    while(data.next())
    {   ui->dataTab->insertRow(row);
        for(int col = 0; col < ui->dataTab->columnCount(); col ++)
            ui->dataTab->setItem(row, col, new QTableWidgetItem(data.value(col).toString()));
        row ++;
    }
}

void FrameCV::on_btAdd_clicked()
{
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Insert Into ChucVu Values('%1', N'%2')").arg(ui->txtMaCV->text(), ui->txtTenCV->text()));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiện thành công!");
        }
        catch(const QString err)
        {
            this->alert("Cảnh báo", "Thao tác thực hiện thất bại");
        }
    }
    else
        this->alert("Cảnh báo", "Không được để trống các trường!");
    this->loadData();
}

void FrameCV::on_btFix_clicked()
{
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Update ChucVu Set TenCV = N'%1' Where MaCV = '%2'").arg(ui->txtTenCV->text(), ui->txtMaCV->text()));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiện thành công!");

        }
        catch(const QString err)
        {
            this->alert("Cảnh báo", "Thao tác thực hiện thất bại");
        }
    }
    else
        this->alert("Cảnh báo", "Chưa chọn chức vụ cần cập nhật");
    this->loadData();
}

void FrameCV::on_btDel_clicked()
{
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Delete ChucVu Where MaCV = '%1'").arg(ui->txtMaCV->text()));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiên thành công!");

        }
        catch(const QString err)
        {
            this->alert("Cảnh báo", "Thao tác thực hiện thất bại");
        }
    }
    else
        this->alert("Cảnh báo", "Chưa chọn chức vụ cần xóa");
    this->loadData();
}

void FrameCV::on_btClear_clicked()
{
    ui->txtMaCV->setText("");
    ui->txtTenCV->setText("");
}

void FrameCV::on_dataTab_cellClicked(int row)
{
    ui->txtMaCV->setText(ui->dataTab->item(row, 0)->text());
    ui->txtTenCV->setText(ui->dataTab->item(row, 1)->text());
}
