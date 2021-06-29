#include "login.h"
#include "ui_login.h"
#include "SQLConnection.h"
#include "mainwindow.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::alert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void Login::on_btLogin_clicked()
{
    QString IDPQ = NULL;
    try
    {
        SQLConnection SQL;
        QSqlQuery data = SQL.queryData(QString("Select MaPQ From Login Where Username = '%1' And Password = '%2'").arg(ui->txtUser->text(), ui->txtPass->text()));
        while(data.next())
        {
            IDPQ = data.value(0).toString();
        }
        if(IDPQ != NULL)
        {
            MainWindow *uiMain = new MainWindow(nullptr, IDPQ.toInt(), ui->txtUser->text(), ui->txtPass->text());
            (*uiMain).show();
            SQL.disConnect();
            this->hide();
        }
        else
        {
            this->alert("Cảnh báo", "Tài khoản hoặc mật khẩu sai");
            SQL.disConnect();
        }
    }
    catch(const QString *err)
    {
        //err = "Không thể kết nối tới database!";
        this->alert("Cảnh báo", "Không thể kết nối tới database");
    }
}

void Login::on_btExit_clicked()
{
    QApplication::quit();
}
