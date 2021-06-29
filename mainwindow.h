#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "framepb.h"
#include "framenv.h"
#include "framecc.h"
#include "framecv.h"
#include "framekt.h"
#include "frametl.h"
#include "framecpass.h"
#include "frameaddtk.h"
#include "frameinfornv.h"
#include "framesearch.h"
#include "frametkcc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, int IDPQ = 0, QString userName = "", QString passWord = "");
    ~MainWindow();

private slots:
    void on_btPhongBan_clicked();

    void on_btNhanVien_clicked();

    void on_btChamCong_clicked();

    void on_btChucVu_clicked();

    void on_btKhenThuong_clicked();

    void on_btTinhLuong_clicked();

    void on_btChangePass_clicked();

    void on_btAddAcc_clicked();

    void on_btChangeInfo_clicked();

    void on_btExit_clicked();

    void on_btSearchNV_clicked();

    void on_btStaticsTimeKeeping_clicked();

private:
    Ui::MainWindow *ui;

    FramePB *UIPB = NULL;
    FrameNV *UINV = NULL;
    FrameCC *UICC = NULL;
    FrameCV *UICV = NULL;
    FrameKT *UIKT = NULL;
    FrameTL *UITL = NULL;
    FrameCPass *UICPass = NULL;
    FrameAddTK *UIAddTK = NULL;
    FrameInforNV *UIInforNV = NULL;
    FrameSearch *UISearch = NULL;
    FrameTKCC *UITKCC = NULL;
    //User control

    int IDPQ;
    QString userName;
    QString passWord;

    QString IDNV;
    void showName();
    void cleanFrame(); // Clean main frame
    void checkPermission();
};

#endif // MAINWINDOW_H
