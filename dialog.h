#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "controlerclass.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0,const QString &path = "");
    ~Dialog();

private slots:
    void on_CanselButton_clicked();
    void on_NextButton_clicked();
    void on_backButton_clicked();
    void on_pushButtonSelectAll_clicked();
    void on_pushButtonRemoveAll_clicked();
    void onItemClicked(QTreeWidgetItem*,int);


private:
    void setCurentPage(int);
    bool ShowMessage(QString value);

private:
    Ui::Dialog *ui;
    int m_currentPage;
    ControlerClass* m_Controller;

};

#endif // DIALOG_H
