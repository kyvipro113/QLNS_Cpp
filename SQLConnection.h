#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
class SQLConnection
{
private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    QString connection_Str = "DRIVER={SQL Server Native Client 11.0};SERVER=MARINKQH_LAN;DATABASE=PythonQLNS;UID=sa;PWD=123456;WSID=.;Trusted_connection=no";
public:
    void queryDataNoReturn(QString query)
    {
        db.setDatabaseName(this->connection_Str);
        db.open();
        QSqlQuery sqlQuery;
        sqlQuery.exec(query);
        if(sqlQuery.lastError().isValid())
            throw "Thao tác thực hiện thất bại";
        db.close();
    }

    QSqlQuery queryData(QString query)
    {
        db.setDatabaseName(this->connection_Str);
        db.open();
        QSqlQuery sqlQuery;
        sqlQuery.exec(query);
        if(sqlQuery.lastError().isValid())
            throw "Thao tác thực hiện thất bại";
        return sqlQuery;
    }

    void disConnect()
    {
        if(db.isOpen())
            db.close();
    }

    bool isOpen()
    {
        return (db.isOpen()) ? true : false;
    }
};
#endif // SQLCONNECTION_H


/*##########################
# Author: Nguyễn Hồng Kỳ   #
# Mail: marinkqh@gmail.com #
# Phone Number: 0386685086 #
# Date: 10/ 2020           #
# Version: 1.1             #
##########################*/
