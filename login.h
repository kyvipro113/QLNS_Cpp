#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btLogin_clicked();

    void on_btExit_clicked();

private:
    Ui::Login *ui;
    void alert(QString title, QString message);
};
#endif // LOGIN_H
