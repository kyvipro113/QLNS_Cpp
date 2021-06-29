#ifndef FRAMECC_H
#define FRAMECC_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"

namespace Ui {
class FrameCC;
}

class FrameCC : public QFrame
{
    Q_OBJECT

public:
    explicit FrameCC(QWidget *parent = nullptr, int statusRadioBT = 2, QString currentDate = "", QString IDNV = "");
    ~FrameCC();

private slots:
    void on_btUpdate_clicked();

    void on_btDel_clicked();

    void on_btLoad_clicked();

    void on_btLoadAgain_clicked();

    void on_deDateCC_dateChanged(const QDate &date);

    void on_radioBTDL_toggled(bool checked);

    void on_radioBTNL_toggled(bool checked);

    void on_dataTab_cellClicked(int row);

    void on_btAdd_clicked();

private:
    Ui::FrameCC *ui;
    int statusRadioBT;
    QString currentDate;
    QString IDNV;

    void loadData();
    void alert(QString title, QString message);
};

#endif // FRAMECC_H
