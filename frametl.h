#ifndef FRAMETL_H
#define FRAMETL_H

#include <QFrame>
#include "SQLConnection.h"
#include <QMessageBox>

namespace Ui {
class FrameTL;
}

class FrameTL : public QFrame
{
    Q_OBJECT

public:
    explicit FrameTL(QWidget *parent = nullptr, QString monthTL = "", QString yearTL = "", QString dateTL = "");
    ~FrameTL();

private slots:
    void on_btTinhLuong_clicked();

    void on_btView_clicked();

    void on_btLoad_clicked();

    void on_deMonth_dateChanged(const QDate &date);

private:
    Ui::FrameTL *ui;
    QString monthTL;
    QString yearTL;
    QString dateTL;
    void loadData();
};

#endif // FRAMETL_H
