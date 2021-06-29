#ifndef FRAMESEARCH_H
#define FRAMESEARCH_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"

namespace Ui {
class FrameSearch;
}

class FrameSearch : public QFrame
{
    Q_OBJECT

public:
    explicit FrameSearch(QWidget *parent = nullptr, int statusRadioBT = 2);
    ~FrameSearch();

private slots:
    void on_radioBTName_toggled(bool checked);

    void on_radioBTID_toggled(bool checked);

    void on_btSearch_clicked();

private:
    Ui::FrameSearch *ui;
    int statusRadioBT;
    void alert(QString title, QString message);
    void loadData(QSqlQuery data);
};

#endif // FRAMESEARCH_H
