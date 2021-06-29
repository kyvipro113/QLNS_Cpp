#include "framenv.h"
#include "ui_framenv.h"
#include <QFileDialog>

FrameNV::FrameNV(QWidget *parent, QString imgFile, QString dateOfBirth, QString idPBGet, QString idCVGet) :
    QFrame(parent),
    ui(new Ui::FrameNV)
{

    ui->setupUi(this);
    this->imgFile = imgFile;
    this->dateOfBirth = dateOfBirth;
    this->idPBGet = idPBGet;
    this->idCVGet = idCVGet;

    ui->comboSex->clear();
    ui->comboSex->addItem("Nam");
    ui->comboSex->addItem("Nữ");

    SQLConnection SQL;
    // Load data from database to combo box
    ui->comboPB->clear();
    QSqlQuery data_PB = SQL.queryData("Select TenPB From PhongBan");
    while(data_PB.next())
    {
        ui->comboPB->addItem(data_PB.value(0).toString());
    }
    SQL.disConnect();
    // Load name PB

    ui->comboCV->clear();
    QSqlQuery data_CV = SQL.queryData("Select TenCV From ChucVu");
    while(data_CV.next())
    {
        ui->comboCV->addItem(data_CV.value(0).toString());
    }
    SQL.disConnect();
    // Load name CV

    this->loadData();
}

FrameNV::~FrameNV()
{
    delete ui;
}

void FrameNV::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

bool FrameNV::checkEmpty()
{
    if(ui->txtIDNV->text() == "" || ui->txtfullName->text() == "" || ui->txtTrinhDo->text() == "" || ui->txtSDT->text() == "" || ui->txtCMT->text() == "" || ui->txtHSL->text() == "")
        return false;
    return true;
}

void FrameNV::loadData()
{
    SQLConnection SQL;

// Show data from database to data table
    QSqlQuery data = SQL.queryData(QString("Select MaNV, TenNV, MaPB, MaCV, GioiTinh, NgaySinh, SDT, CMT, TrinhDo, HSL from NhanVien"));
    ui->dataTab->setRowCount(0);
    int row = 0;
    while(data.next())
    {
        ui->dataTab->insertRow(row);
        for(int colmn = 0; colmn < ui->dataTab->columnCount(); colmn ++)
            ui->dataTab->setItem(row, colmn, new QTableWidgetItem(data.value(colmn).toString()));
        row ++;
    }
    SQL.disConnect();

    for(int row_number = 0; row_number < ui->dataTab->rowCount(); row_number ++)
    {
        QString itemIDPB = ui->dataTab->item(row_number,2)->text();
        QSqlQuery data_NamePB = SQL.queryData(QString("Select TenPB From PhongBan Where MaPB = '%1'").arg(itemIDPB));
        while(data_NamePB.next())
        {
            ui->dataTab->setItem(row_number, 2, new QTableWidgetItem(data_NamePB.value(0).toString()));
        }
    }
    SQL.disConnect();
    // get name pb
    for(int row_number = 0; row_number < ui->dataTab->rowCount(); row_number ++)
    {
        QString itemIDCV = ui->dataTab->item(row_number, 3)->text();
        QSqlQuery data_NameCV = SQL.queryData(QString("Select TenCV From ChucVu Where MaCV = '%1'").arg(itemIDCV));
        while(data_NameCV.next())
        {
            ui->dataTab->setItem(row_number, 3, new QTableWidgetItem(data_NameCV.value(0).toString()));
        }
    }
    SQL.disConnect();
    // get name cv
}

void FrameNV::cleanText()
{
    ui->txtIDNV->setText("");
    ui->txtfullName->setText("");;
    ui->comboPB->setCurrentIndex(0);
    ui->comboCV->setCurrentIndex(0);
    ui->comboSex->setCurrentIndex(0);
    ui->deDateOfBirth->setDate(QDate(2000, 1, 1));
    ui->lbImg->setText("Image");
    ui->txtSDT->setText("");
    ui->txtCMT->setText("");
    ui->txtTrinhDo->setText("");
    ui->txtHSL->setText("");
}

void FrameNV::getID_PB_CV()
{
    SQLConnection SQL;
    // ID Phong Ban
    QSqlQuery data_IDPB = SQL.queryData(QString("Select MaPB From PhongBan Where TenPB = N'%1'").arg(ui->comboPB->currentText()));
    while(data_IDPB.next())
        this->idPBGet = data_IDPB.value(0).toString();
    SQL.disConnect();
    // ID Chuc Vu
    QSqlQuery data_IDCV = SQL.queryData(QString("Select MaCV From ChucVu Where TenCV = N'%1'").arg(ui->comboCV->currentText()));
    while(data_IDCV.next())
        this->idCVGet = data_IDCV.value(0).toString();
    SQL.disConnect();
}


void FrameNV::on_btAdd_clicked()
{
    this->getID_PB_CV();
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Insert Into Login Values('%1', null, null, null)").arg(ui->txtIDNV->text()));
            SQL.queryDataNoReturn(QString("Insert Into NhanVien Values ('%1', N'%2', '%3', '%4', N'%5', '%6', '%7', '%8', '%9', N'%10', '%11' )")
                                  .arg(ui->txtIDNV->text(), ui->txtfullName->text(), this->idPBGet, this->idCVGet, ui->comboSex->currentText(),
                                       this->dateOfBirth, this->imgFile, ui->txtSDT->text(), ui->txtCMT->text(), ui->txtTrinhDo->text(), ui->txtHSL->text()));
           SQL.disConnect();
           this->alert("Thông báo", "Thao tác thực hiện thành công!");
        }
        catch(...)
        {
            QString err = "Thao tác thực hiện thất bại!";
            this->alert("Cảnh báo", err);
        }
    }
    else
        this->alert("Cảnh báo", "Không được để trống các trường!");
    this->loadData();
}

void FrameNV::on_btFix_clicked()
{
    this->getID_PB_CV();
    if(checkEmpty())
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Update NhanVien Set TenNV = N'%1', MaPB = '%2', MaCV = '%3', GioiTinh = N'%4', NgaySinh = '%5', Anh = '%6', SDT = '%7', CMT = '%8', TrinhDo = N'%9', HSL = '%10' Where MaNV = '%11'")
                                  .arg(ui->txtfullName->text(), this->idPBGet, this->idCVGet, ui->comboSex->currentText(), this->dateOfBirth,
                                       this->imgFile, ui->txtSDT->text(), ui->txtCMT->text(), ui->txtTrinhDo->text(), ui->txtHSL->text(), ui->txtIDNV->text()));
            SQL.disConnect();
            this->alert("Thông báo", "Thao tác thực hiện thành công!");
        }
        catch(QString err)
        {
            err = "Thao tác thực hiện thắt bại!";
            this->alert("Cảnh báo", err);
        }
    }
    else
        this->alert("Cảnh báo", "Không được để trống các trường!");
    this->loadData();
}

void FrameNV::on_btDel_clicked()
{
    if(ui->txtIDNV->text() != "")
    {
        try
        {
            SQLConnection SQL;
            SQL.queryDataNoReturn(QString("Exec deleteNV @MaNV = '%1'").arg(ui->txtIDNV->text()));
            SQL.disConnect();
            SQL.disConnect();
            QMessageBox msgBox;
            this->alert("Thông báo", "Thao tác thực hiện thành công!");
        }
        catch(QString err)
        {
            err = "Thao tác thực hiện thắt bại!";
            this->alert("Cảnh báo", err);
        }
    }
    else
        this->alert("Cảnh báo", "Chưa chọn nhân viên cần xóa!");
    this->loadData();
}

void FrameNV::on_btClear_clicked()
{
   this->cleanText();
}

void FrameNV::on_btChoose_clicked()
{
    // Open file dialog
    QFileDialog dialogWindow(this);
    QString imageFile = QFileDialog::getOpenFileName(this, tr("Chọn ảnh nhân viên"), "../QLNS_Cpp/image Employee", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->lbImg->setPixmap(QPixmap(imageFile));
    QStringList listPath = imageFile.split(QLatin1Char('/'));
    this->imgFile = listPath.last();
    //qDebug() << this->imgFile;
    //QString fileDirec = "../QLNS_Cpp/image Employee/";
    //qDebug() << fileDirec;
    //QString filePath = fileDirec + listPath.last();
    //qDebug() << filePath;
}

void FrameNV::on_deDateOfBirth_userDateChanged(const QDate &date)
{

    QString year, month, day, ch = "/";
    year = QString::number(date.year());
    month = QString::number(date.month());
    day = QString::number(date.day());
    this->dateOfBirth = year + ch + month + ch + day;
    //qDebug() << this->dateOfBirth;
}

void FrameNV::on_dataTab_cellClicked(int row)
{
    QString IDNV = ui->dataTab->item(row, 0)->text();
    ui->txtIDNV->setText(IDNV);
    ui->txtfullName->setText(ui->dataTab->item(row, 1)->text());
    ui->comboPB->setCurrentText(ui->dataTab->item(row, 2)->text());
    ui->comboCV->setCurrentText(ui->dataTab->item(row, 3)->text());
    ui->comboSex->setCurrentText(ui->dataTab->item(row, 4)->text());

    // date of birth
    QString birthDay = ui->dataTab->item(row, 5)->text();
    //qDebug() << birthDay;
    //qDebug() << birthDay.split(QLatin1Char('-'))[0].toInt();
    this->dateOfBirth = birthDay;
    //qDebug() << this->dateOfBirth;
    QDate date = QDate(birthDay.split(QLatin1Char('-'))[0].toInt(), birthDay.split(QLatin1Char('-'))[1].toInt(), birthDay.split(QLatin1Char('-'))[2].toInt());
    ui->deDateOfBirth->setDate(date);

    // image
    SQLConnection SQL;
    QSqlQuery data_image = SQL.queryData(QString("Select Anh from NhanVien Where MaNV = '%1'").arg(IDNV));
    while(data_image.next())
        this->imgFile = data_image.value(0).toString();
    SQL.disConnect();
    QString fileDirec = "../QLNS_Cpp/image Employee/";
    QString filePath = fileDirec + this->imgFile;
    ui->lbImg->setPixmap(QPixmap(filePath));

    ui->txtSDT->setText(ui->dataTab->item(row, 6)->text());
    ui->txtCMT->setText(ui->dataTab->item(row, 7)->text());
    ui->txtTrinhDo->setText(ui->dataTab->item(row, 8)->text());
    ui->txtHSL->setText(ui->dataTab->item(row, 9)->text());
}
