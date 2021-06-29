#ifndef FRAMECV_H
#define FRAMECV_H

#include <QFrame>
#include "SQLConnection.h"

namespace Ui {
class FrameCV;
}

class FrameCV : public QFrame
{
    Q_OBJECT

public:
    explicit FrameCV(QWidget *parent = nullptr);
    ~FrameCV();

private slots:
    void on_btAdd_clicked();

    void on_btFix_clicked();

    void on_btDel_clicked();

    void on_btClear_clicked();

    void on_dataTab_cellClicked(int row);

private:
    Ui::FrameCV *ui;
    void loadData();
    void alert(QString title, QString message);
    bool checkEmpty();
};

#endif // FRAMECV_H
