#include "frameinfornv.h"
#include "ui_frameinfornv.h"

FrameInforNV::FrameInforNV(QWidget *parent, QString dateOfBirth, QString IDNV) :
    QFrame(parent),
    ui(new Ui::FrameInforNV)
{
    ui->setupUi(this);
    ui->comboSex->addItem("Nam");
    ui->comboSex->addItem("Nữ");
    this->dateOfBirth = dateOfBirth;
    this->IDNV = IDNV;
    this->loadData();
}

void FrameInforNV::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void FrameInforNV::processDate(QString date)
{
    QDate birthDay = QDate(date.split(QLatin1Char('-'))[0].toInt(), date.split(QLatin1Char('-'))[1].toInt(), date.split(QLatin1Char('-'))[2].toInt());
    ui->deDateOfBirth->setDate(birthDay);
}

FrameInforNV::~FrameInforNV()
{
    delete ui;
}

void FrameInforNV::loadData()
{
    ui->lbIDNV->setText(this->IDNV);
    SQLConnection SQL;
    QSqlQuery data = SQL.queryData(QString("Select TenNV, GioiTinh, NgaySinh, SDT, CMT From NhanVien Where MaNV = '%1'").arg(this->IDNV));
    while(data.next())
    {
        ui->txtTenNV->setText(data.value(0).toString());
        ui->comboSex->setCurrentText(data.value(1).toString());
        this->processDate(data.value(2).toString());
        ui->txtSDT->setText(data.value(3).toString());
        ui->txtCMT->setText(data.value(4).toString());
    }
    SQL.disConnect();
}

void FrameInforNV::on_btUpdate_clicked()
{
    try
    {
        SQLConnection SQL;
        SQL.queryDataNoReturn(QString("Update NhanVien Set TenNV = N'%1', GioiTinh = N'%2', NgaySinh = '%3', SDT = '%4', CMT = '%5' Where MaNV = '%6'")
                              .arg(ui->txtTenNV->text(), ui->comboSex->currentText(), this->dateOfBirth, ui->txtSDT->text(), ui->txtCMT->text(), this->IDNV));
        SQL.disConnect();

        this->alert("Thông báo", "Thao tác thực hiện thành công!");
    }
    catch(QString err)
    {
        this->alert("Cảnh báo", "Thao tác thực hiện thất bại!");
    }
    this->loadData();
}

void FrameInforNV::on_deDateOfBirth_dateChanged(const QDate &date)
{
    QString year, month, day, ch = "/";
    year = QString::number(date.year());
    month = QString::number(date.month());
    day = QString::number((date.day()));
    this->dateOfBirth = year + ch + month + ch + day;
}
