#ifndef FRAMEKT_H
#define FRAMEKT_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"
namespace Ui {
class FrameKT;
}

class FrameKT : public QFrame
{
    Q_OBJECT

public:
    explicit FrameKT(QWidget *parent = nullptr, QString currentDate = "", int statusRadioBT = 2, QString IDNV = "");
    ~FrameKT();

private slots:
    void on_btAdd_clicked();

    void on_btDel_clicked();

    void on_btClear_clicked();

    void on_deDate_dateChanged(const QDate &date);

    void on_radioBTKhenThuong_toggled(bool checked);

    void on_radioBTKyLuat_toggled(bool checked);

    void on_dataTabNhanVien_cellClicked(int row);

    void on_dataTabKhenThuong_cellClicked(int row);

    void on_dataTabKyLuat_cellClicked(int row);

private:
    Ui::FrameKT *ui;
    QString currentDate;
    int statusRadioBT;
    QString IDNV;

    void loadData();
    void alert(QString title, QString message);
    void cleanText();
    bool checkEmpty();
};

#endif // FRAMEKT_H
