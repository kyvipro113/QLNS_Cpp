#include "framecpass.h"
#include "ui_framecpass.h"

FrameCPass::FrameCPass(QWidget *parent, QString username, QString passwordOld) :
    QFrame(parent),
    ui(new Ui::FrameCPass)
{
    ui->setupUi(this);
    this->username = username;
    this->passwordOld =  passwordOld;
}

FrameCPass::~FrameCPass()
{
    delete ui;
}

void FrameCPass::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

bool FrameCPass::checkOldPassword()
{
    return (ui->txtMKOld->text() == this->passwordOld) ? true : false;
}

bool FrameCPass::checkNewPassword()
{
    return (ui->txtMKNewAgain->text() == ui->txtMKNew->text()) ? true : false;
}

void FrameCPass::on_btConfirm_clicked()
{
    try
    {
        SQLConnection SQL;
        if(checkOldPassword())
        {
            if(checkNewPassword())
            {
                SQL.queryDataNoReturn(QString("Update Login Set Password = '%1' Where Username = '%2'").arg(ui->txtMKNew->text(), this->username));
                SQL.disConnect();

                this->alert("Thông báo", "Thao tác thực hiện thành công!");
            }
            else
            {
               this->alert("Cảnh báo", "Mật khẩu mới không trùng nhau");
            }
        }
        else
        {
            this->alert("Cảnh báo", "Mật khẩu cũ không đúng");
        }


    }
    catch(const QString err)
    {
        this->alert("Cảnh báo", err);
    }
}

void FrameCPass::on_btExit_clicked()
{
    ui->txtMKOld->setText("");
    ui->txtMKNew->setText("");
    ui->txtMKNewAgain->setText("");
}
