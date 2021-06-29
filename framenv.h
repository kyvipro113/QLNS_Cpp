#ifndef FRAMENV_H
#define FRAMENV_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"

namespace Ui {
class FrameNV;
}

class FrameNV : public QFrame
{
    Q_OBJECT

public:
    explicit FrameNV(QWidget *parent = nullptr, QString imgFile = "", QString dateOfBirth = "",QString idPBGet = "", QString idCVGet = "");
    ~FrameNV();

private slots:
    void on_btAdd_clicked();

    void on_btFix_clicked();

    void on_btDel_clicked();

    void on_btClear_clicked();

    void on_btChoose_clicked();

    void on_deDateOfBirth_userDateChanged(const QDate &date);

    void on_dataTab_cellClicked(int row);

private:
    Ui::FrameNV *ui;

    QString imgFile;
    QString dateOfBirth;
    QString idPBGet;
    QString idCVGet;

    void loadData();
    void getID_PB_CV();
    void alert(QString title, QString message);
    bool checkEmpty();
    void cleanText();
};

#endif // FRAMENV_H
