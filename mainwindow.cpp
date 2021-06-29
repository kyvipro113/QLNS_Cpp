#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SQLConnection.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent, int IDPQ, QString userName, QString passWord) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->IDPQ = IDPQ;
    this->userName = userName;
    this->passWord = passWord;
    this->showName();
    this->checkPermission();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkPermission()
{
    if(this->IDPQ == 3)
    {
        ui->btAddAcc->setEnabled(false);
        ui->btPhongBan->setEnabled(false);
        ui->btNhanVien->setEnabled(false);
        ui->btChucVu->setEnabled(false);
    }

    if(this->IDPQ == 2)
    {
        ui->btPhongBan->setEnabled(false);
    }
}

void MainWindow::cleanFrame()
{
    if(this->UIPB)
    {
        this->UIPB->~FramePB();
        this->UIPB = NULL;
    }
    if(this->UINV)
    {
        this->UINV->~FrameNV();
        this->UINV = NULL;
    }
    if(this->UICC)
    {
        this->UICC->~FrameCC();
        this->UICC = NULL;
    }
    if(this->UICV)
    {
        this->UICV->~FrameCV();
        this->UICV = NULL;
    }
    if(this->UIKT)
    {
        this->UIKT->~FrameKT();
        this->UIKT = NULL;
    }
    if(this->UITL)
    {
        this->UITL->~FrameTL();
        this->UITL = NULL;
    }
    // Management Feature
    if(this->UICPass)
    {
        this->UICPass->~FrameCPass();
        this->UICPass = NULL;
    }
    if(this->UIAddTK)
    {
        this->UIAddTK->~FrameAddTK();
        this->UIAddTK = NULL;
    }
    if(this->UIInforNV)
    {
        this->UIInforNV->~FrameInforNV();
        this->UIInforNV = NULL;
    }
    // System Feature
    if(this->UISearch)
    {
        this->UISearch->~FrameSearch();
        this->UISearch = NULL;
    }
    if(this->UITKCC)
    {
        this->UITKCC->~FrameTKCC();
        this->UITKCC = NULL;
    }
    // Extra Feature

}

void MainWindow::showName()
{
    SQLConnection SQL;
    QString queryData = QString("Select NhanVien.TenNV, NhanVien.MaNV From NhanVien, Login Where NhanVien.MaNV = Login.MaNV And Login.MaPQ = %1 And Login.Username = '%2' ").arg(this->IDPQ).arg(this->userName);;
    QSqlQuery data = SQL.queryData(queryData);
    while(data.next())
    {
        ui->lbHello->setText(QString("Xin chào %2").arg(data.value(0).toString()));
        this->IDNV = data.value(1).toString();
    }
    SQL.disConnect();
}

void MainWindow::on_btPhongBan_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UIPB = new FramePB(ui->mainFrame);
    ui->mainFrame->show();

}

void MainWindow::on_btNhanVien_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UINV = new FrameNV(ui->mainFrame, "", "", "", "");
    ui->mainFrame->show();
}

void MainWindow::on_btChamCong_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UICC = new FrameCC(ui->mainFrame, 2, "", "");
    ui->mainFrame->show();
}

void MainWindow::on_btChucVu_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UICV = new FrameCV(ui->mainFrame);
    ui->mainFrame->show();
}

void MainWindow::on_btKhenThuong_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UIKT = new FrameKT(ui->mainFrame, "", 2, "");
    ui->mainFrame->show();
}

void MainWindow::on_btTinhLuong_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UITL = new FrameTL(ui->mainFrame, "", "", "");
    ui->mainFrame->show();
}

void MainWindow::on_btChangePass_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UICPass = new FrameCPass(ui->mainFrame, this->userName, this->passWord);
    ui->mainFrame->show();
}

void MainWindow::on_btAddAcc_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UIAddTK = new FrameAddTK(ui->mainFrame);
    ui->mainFrame->show();
}

void MainWindow::on_btChangeInfo_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UIInforNV = new FrameInforNV(ui->mainFrame, "", this->IDNV);
    ui->mainFrame->show();
}

void MainWindow::on_btExit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_btSearchNV_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UISearch = new FrameSearch(ui->mainFrame, 2);
    ui->mainFrame->show();
}

void MainWindow::on_btStaticsTimeKeeping_clicked()
{
    ui->mainFrame->hide();
    this->cleanFrame();
    this->UITKCC = new FrameTKCC(ui->mainFrame, 2, "");
    ui->mainFrame->show();
}
