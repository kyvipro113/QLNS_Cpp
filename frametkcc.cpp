#include "frametkcc.h"
#include "ui_frametkcc.h"

FrameTKCC::FrameTKCC(QWidget *parent, int statusRadioBT, QString currentDate) :
    QFrame(parent),
    ui(new Ui::FrameTKCC)
{
    ui->setupUi(this);
    this->statusRadioBT = statusRadioBT;
    this->currentDate = currentDate;
}

FrameTKCC::~FrameTKCC()
{
    delete ui;
}

void FrameTKCC::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void FrameTKCC::loadData(QSqlQuery data)
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

void FrameTKCC::on_deDate_dateChanged(const QDate &date)
{
    QString year, month, day, ch = "/";
    year = QString::number(date.year());
    month = QString::number(date.month());
    day = QString::number(date.day());
    this->currentDate = year + ch + month + ch + day;
}

void FrameTKCC::on_radioBTDL_clicked(bool checked)
{
    if(checked)
        this->statusRadioBT = 0;
}

void FrameTKCC::on_radioBTNL_toggled(bool checked)
{
    if(checked)
        this->statusRadioBT = 1;
}

void FrameTKCC::on_btLoad_clicked()
{
    SQLConnection SQL;
    QSqlQuery data;
    if(statusRadioBT == 2)
        this->alert("Cảnh báo", "Chưa chọn trạng thái chấm công!");
    else if(statusRadioBT == 0)
    {
        data = SQL.queryData(QString("Select * From ChamCong Where Ngay = '%1' and TrangThai = N'Đi Làm'").arg(this->currentDate));
        this->loadData(data);
        SQL.disConnect();
        this->alert("Thông báo", "Thao tác thực hiện thành công!");
    }
    else if(statusRadioBT == 1)
    {
        data = SQL.queryData(QString("Select * From ChamCong Where Ngay = '%1'and TrangThai = N'Nghỉ'").arg(this->currentDate));
        this->loadData(data);
        SQL.disConnect();
        this->alert("Thông báo", "Thao tác thực hiện thành công!");
    }

}
