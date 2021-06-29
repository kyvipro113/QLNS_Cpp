#ifndef FRAMETKCC_H
#define FRAMETKCC_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"

namespace Ui {
class FrameTKCC;
}

class FrameTKCC : public QFrame
{
    Q_OBJECT

public:
    explicit FrameTKCC(QWidget *parent = nullptr, int statusRadioBT = 2, QString curentDate = "");
    ~FrameTKCC();

private slots:
    void on_deDate_dateChanged(const QDate &date);

    void on_radioBTDL_clicked(bool checked);

    void on_radioBTNL_toggled(bool checked);

    void on_btLoad_clicked();

private:
    Ui::FrameTKCC *ui;
    int statusRadioBT;
    QString currentDate;

    void alert(QString title, QString message);
    void loadData(QSqlQuery data);
};

#endif // FRAMETKCC_H
