#ifndef FRAMECPASS_H
#define FRAMECPASS_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"

namespace Ui {
class FrameCPass;
}

class FrameCPass : public QFrame
{
    Q_OBJECT

public:
    explicit FrameCPass(QWidget *parent = nullptr, QString username = "", QString passwordOld = "");
    ~FrameCPass();

private slots:
    void on_btConfirm_clicked();

    void on_btExit_clicked();

private:
    Ui::FrameCPass *ui;
    QString passwordOld;
    QString username;
    void alert(QString title, QString message);
    bool checkOldPassword();
    bool checkNewPassword();
};

#endif // FRAMECPASS_H
