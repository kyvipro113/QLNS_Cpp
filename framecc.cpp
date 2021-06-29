#include "framecc.h"
#include "ui_framecc.h"
#include <QDebug>

FrameCC::FrameCC(QWidget *parent, int statusRadioBT, QString currentDate, QString IDNV) :
    QFrame(parent),
    ui(new Ui::FrameCC)
{
    ui->setupUi(this);
    this->statusRadioBT = statusRadioBT;
    this->currentDate = currentDate;
    this->IDNV = IDNV;
    this->loadData();
}

FrameCC::~FrameCC()
{
    delete ui;
}

void FrameCC::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void FrameCC::loadData()
{
    SQLConnection SQL;
    QSqlQuery data = SQL.queryData("Select * From ChamCong");
    int row = 0;
    ui->dataTab->setRowCount(0);
    while(data.next())
    {
        ui->dataTab->insertRow(row);
        for(int col = 0; col < ui->dataTab->columnCount(); col ++)
            ui->dataTab->setItem(row, col, new QTableWidgetItem(data.value(col).toString()));
        row ++;
    }
    SQL.disConnect();

    for(int row = 0; row < ui->dataTab->rowCount(); row ++)
    {
        QString IDNV = ui->dataTab->item(row, 0)->text();
        QSqlQuery data_IDNV = SQL.queryData(QString("Select TenNV From NhanVien Where MaNV = '%1'").arg(IDNV));
        while(data_IDNV.next())
            ui->dataTab->setItem(row, 0, new QTableWidgetItem(data_IDNV.value(0).toString()));
        SQL.disConnect();
    }
    ui->lbTenNV->setText("");
    ui->checkAllCC->setChecked(false);
    ui->radioBTDL->setChecked(false);
    ui->radioBTNL->setChecked(false);
}

void FrameCC::on_btUpdate_clicked()
{
    try
    {
        SQLConnection SQL;
        if(ui->checkAllCC->isChecked())
        {
            if(this->statusRadioBT == 0)
            {
                SQL.queryDataNoReturn(QString("Update ChamCong Set TrangThai = N'Đi Làm' Where Ngay = '%1'").arg(this->currentDate));
                SQL.disConnect();

                this->alert("Thông báo", "Thao tác thực hiện thành công");
            }
            else if(this->statusRadioBT == 1)
            {
                SQL.queryDataNoReturn(QString("Update ChamCong Set TrangThai = N'Nghỉ' Where Ngay = '%2'").arg(this->currentDate));
                SQL.disConnect();

                this->alert("Thông báo", "Thao tác thực hiện thành công");
            }
            else
            {
                this->alert("Cảnh báo", "Chưa chọn trạng thái chấm công!");
            }

        }
        else
        {
            if(ui->lbTenNV->text() == "")
            {
                this->alert("Cảnh báo", "Chưa chọn nhân viên!");
            }
            else
            {
                if(this->statusRadioBT == 0)
                {
                    QSqlQuery data_IDNV = SQL.queryData(QString("Select MaNV From NhanVien Where TenNV = N'%1'").arg(ui->lbTenNV->text()));
                    while(data_IDNV.next())
                    {
                        QString IDNV = data_IDNV.value(0).toString();
                        SQL.queryDataNoReturn(QString("Update ChamCong Set TrangThai = N'Đi Làm' Where MaNV = '%1' And Ngay = '%2'").arg(IDNV, this->currentDate));
                    }
                    SQL.disConnect();

                    this->alert("Thông báo", "Thao tác thực hiện thành công");
                }
                else if(this->statusRadioBT == 1)
                {
                    QSqlQuery data_IDNV = SQL.queryData(QString("Select MaNV From NhanVien Where TenNV = N'%1'").arg(ui->lbTenNV->text()));
                    while(data_IDNV.next())
                    {
                        QString IDNV = data_IDNV.value(0).toString();
                        SQL.queryDataNoReturn(QString("Update ChamCong Set TrangThai = N'Nghỉ' Where MaNV = '%1' And Ngay = '%2'").arg(IDNV, this->currentDate));
                    }
                    SQL.disConnect();

                    this->alert("Thông báo", "Thao tác thực hiện thành công!");
                }
            }
        }
    }
    catch(const QString *err)
    {
        this->alert("Cảnh báo", "Thao tác thực hiện thất bại");
    }
    this->loadData();
}

void FrameCC::on_btDel_clicked()
{
    try
    {
        SQLConnection SQL;
        if(ui->checkAllCC->isChecked())
        {
            SQL.queryDataNoReturn(QString("Delete ChamCong Where Ngay = '%1'").arg(this->currentDate));
            SQL.disConnect();
            QMessageBox msgBox;
            msgBox.setText("Thao tác thực hiện thành công!");
            msgBox.setWindowTitle("Cảnh báo");
            msgBox.exec();
        }
        else
        {
            if(ui->lbTenNV->text() == "")
            {
                QMessageBox msgBox;
                msgBox.setText("Chưa chọn nhân viên chấm công!");
                msgBox.setWindowTitle("Cảnh báo");
                msgBox.exec();
            }
            else
            {
                QSqlQuery data_IDNV = SQL.queryData(QString("Select MaNV From NhanVien Where TenNV = N'%1'").arg(ui->lbTenNV->text()));
                while(data_IDNV.next())
                {
                    QString IDNV = data_IDNV.value(0).toString();
                    qDebug() << IDNV;
                    SQL.queryDataNoReturn(QString("Delete ChamCong Where MaNV = '%1' And Ngay = '%2'").arg(IDNV, this->currentDate));
                }
                SQL.disConnect();

                QMessageBox msgBox;
                msgBox.setText("Thao tác thực hiện thành công!");
                msgBox.setWindowTitle("Cảnh báo");
                msgBox.exec();
            }
        }
    }
    catch(QString err)
    {
        err = "Thao tác thực hiện thất bại!";
        QMessageBox msgBox;
        msgBox.setText(err);
        msgBox.setWindowTitle("Cảnh báo");
        msgBox.exec();
    }
    this->loadData();
}

void FrameCC::on_btLoad_clicked()
{
    SQLConnection SQL;
    QSqlQuery data = SQL.queryData(QString("Select * From ChamCong Where Ngay = '%1'").arg(this->currentDate));
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

    for(int row = 0; row < ui->dataTab->rowCount(); row ++)
    {
        QString IDNV = ui->dataTab->item(row, 0)->text();
        QSqlQuery data_IDNV = SQL.queryData(QString("Select TenNV From NhanVien Where MaNV = '%1'").arg(IDNV));
        while(data_IDNV.next())
            ui->dataTab->setItem(row, 0, new QTableWidgetItem(data_IDNV.value(0).toString()));
        SQL.disConnect();
    }
}

void FrameCC::on_btLoadAgain_clicked()
{
    this->loadData();
}

void FrameCC::on_deDateCC_dateChanged(const QDate &date)
{
    QString year, month, day, ch = "/";
    year = QString::number(date.year());
    month = QString::number(date.month());
    day = QString::number(date.day());
    this->currentDate = year + ch + month + ch + day;
    //qDebug() << this->currentDate;
}

void FrameCC::on_radioBTDL_toggled(bool checked)
{
    if(checked)
        this->statusRadioBT = 0;
}

void FrameCC::on_radioBTNL_toggled(bool checked)
{
    if(checked)
        this->statusRadioBT = 1;
}

void FrameCC::on_dataTab_cellClicked(int row)
{
    ui->lbTenNV->setText(ui->dataTab->item(row, 0)->text());
    SQLConnection SQL;
    QSqlQuery data_IDNV = SQL.queryData(QString("Select MaNV From NhanVien Where TenNV = N'%1'").arg(ui->dataTab->item(row, 0)->text()));
    while(data_IDNV.next())
        this->IDNV = data_IDNV.value(0).toString();

    QDate date = QDate(ui->dataTab->item(row, 1)->text().split(QLatin1Char('-'))[0].toInt(),
            ui->dataTab->item(row, 1)->text().split(QLatin1Char('-'))[1].toInt(),
            ui->dataTab->item(row, 1)->text().split(QLatin1Char('-'))[2].toInt());
    ui->deDateCC->setDate(date);

    if(ui->dataTab->item(row, 2)->text() == "Đi Làm")
        ui->radioBTDL->setChecked(true);
    else
        ui->radioBTNL->setChecked(true);

    ui->checkAllCC->setChecked(false);
}

void FrameCC::on_btAdd_clicked()
{
    try
    {
        SQLConnection SQL;
        if(ui->checkAllCC->isChecked())
        {
            QVector <QString> IDEmployee;
            QSqlQuery data_NV = SQL.queryData("Select MaNV From NhanVien");
            while(data_NV.next())
                IDEmployee.append(data_NV.value(0).toString());
            SQL.disConnect();
            for(QString itemID : IDEmployee)
                SQL.queryDataNoReturn(QString("Insert Into ChamCong Values ('%1', '%2', N'Đi Làm')").arg(itemID, this->currentDate));
            SQL.disConnect();

            QMessageBox msgBox;
            this->alert("Thông báo", "Thao tác thực hiện thành công!");
        }
        else
        {
            if(ui->lbTenNV->text() == "")
            {
               this->alert("Cảnh báo", "Chưa chọn nhân viên!");
            }
            else
            {
                if(this->statusRadioBT == 0)
                {
                    QSqlQuery data_IDNV = SQL.queryData(QString("Select MaNV From NhanVien Where TenNV = N'%1'").arg(ui->lbTenNV->text()));
                    while(data_IDNV.next())
                    {
                        QString IDNV = data_IDNV.value(0).toString();
                        SQL.queryDataNoReturn(QString("Insert Into ChamCong Values ('%1', '%2', N'Đi Làm')").arg(IDNV, this->currentDate));
                    }
                    SQL.disConnect();
                }
                if(this->statusRadioBT == 1)
                {
                    QSqlQuery data_IDNV = SQL.queryData(QString("Select MaNV From NhanVien Where TenNV = N'%1'").arg(ui->lbTenNV->text()));
                    while(data_IDNV.next())
                    {
                        QString IDNV = data_IDNV.value(0).toString();
                        SQL.queryDataNoReturn(QString("Insert Into ChamCong Values ('%1', '%2', N'Nghỉ')").arg(IDNV, this->currentDate));
                    }
                    SQL.disConnect();
                }
                this->alert("Thông báo", "Thao tác thực hiện thành công!");
            }
        }
    }
    catch(const QString err)
    {
        this->alert("Cảnh báo", "Thao tác thực hiện thất bại");
    }
    this->loadData();
}
