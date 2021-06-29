#ifndef FRAMEADDTK_H
#define FRAMEADDTK_H

#include <QFrame>
#include <QMessageBox>
#include "SQLConnection.h"

namespace Ui {
class FrameAddTK;
}

class FrameAddTK : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddTK(QWidget *parent = nullptr);
    ~FrameAddTK();

private slots:

    void on_btFix_clicked();

    void on_btDel_clicked();

    void on_btClear_clicked();

    void on_dataTabDSNV_cellClicked(int row);

    void on_dataTabDSTK_cellClicked(int row);

private:
    Ui::FrameAddTK *ui;

    void alert(QString title, QString message);
    QString getIDpermission();
    void loadData();
};

#endif // FRAMEADDTK_H
