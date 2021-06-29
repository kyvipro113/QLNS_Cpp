#ifndef FRAMEINFORNV_H
#define FRAMEINFORNV_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"

namespace Ui {
class FrameInforNV;
}

class FrameInforNV : public QFrame
{
    Q_OBJECT

public:
    explicit FrameInforNV(QWidget *parent = nullptr, QString dateOfBirth = "", QString IDNV = "");
    ~FrameInforNV();

private slots:
    void on_btUpdate_clicked();

    void on_deDateOfBirth_dateChanged(const QDate &date);

private:
    Ui::FrameInforNV *ui;
    QString dateOfBirth;
    QString IDNV;

    void loadData();
    void processDate(QString date);
    void alert(QString title, QString message);
};

#endif // FRAMEINFORNV_H
