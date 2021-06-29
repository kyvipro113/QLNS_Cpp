#ifndef FRAMEPB_H
#define FRAMEPB_H

#include <QFrame>
#include "SQLConnection.h"
#include <QMessageBox>

namespace Ui {
class FramePB;
}

class FramePB : public QFrame
{
    Q_OBJECT

public:
    explicit FramePB(QWidget *parent = nullptr);
    ~FramePB();

private slots:
    void on_btAdd_clicked();

    void on_btFix_clicked();

    void on_btDel_clicked();

    void on_btClear_clicked();

    void on_dataTab_cellClicked(int row);

private:
    Ui::FramePB *ui;
    void loadData();
    bool checkEmpty();
    void alert(QString title, QString message);
};

#endif // FRAMEPB_H
