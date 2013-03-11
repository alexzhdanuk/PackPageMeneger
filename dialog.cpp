#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent,const QString &path) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Update the program");
    ui->backButton->setText("< Back");
    ui->NextButton->setText("Next >");
    ui->CanselButton->setText("Cansel");
    ui->radioButtonCustomUpdate->setText("Custom update the program");
    ui->radioButtonStandartUpdate->setText("Standart update the program");
    ui->radioButtonExitFromUpdate->setText("Exit from update program");
    ui->ProgressLabel->setText("");
    ui->pushButtonRemoveAll->setText("Clear All");
    ui->pushButtonSelectAll->setText("Select All");
    ui->TreeWidget->setWindowTitle("Package manager");
    ui->ProgressBar->setValue(0);
    m_currentPage = 1;

    setCurentPage(m_currentPage);

    m_Controller = new ControlerClass(0,path);
    m_Controller->setupStartOptions(ui->TreeWidget);
    connect(m_Controller,SIGNAL(closeProgram()),this,SLOT(on_CanselButton_clicked()));
    connect(ui->TreeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onItemClicked(QTreeWidgetItem*,int)));
}


void Dialog::setCurentPage(int val)
{
    switch(val)
    {
        case 1:
        {
            //видимые элементы
            ui->LayoutGeneralFormButtons->setEnabled(true);
            ui->backButton->setVisible(true);
            ui->CanselButton->setVisible(true);
            ui->NextButton->setVisible(true);
            ui->LayoutQuestion->setEnabled(true);
            ui->radioButtonCustomUpdate->setVisible(true);
            ui->radioButtonExitFromUpdate->setVisible(true);
            ui->radioButtonStandartUpdate->setVisible(true);

            //не видимые элементы
            ui->LayoutNumber2->setEnabled(false);
            ui->gridLayout_2->setEnabled(false);
            ui->TreeWidget->setVisible(false);
            ui->pushButtonRemoveAll->setVisible(false);
            ui->pushButtonSelectAll->setVisible(false);
            ui->LayoutProgresBar->setEnabled(false);
            ui->ProgressBar->setVisible(false);
            ui->ProgressLabel->setVisible(false);
        }
        break;
        case 2:
        {
            //видимые элементы
            ui->LayoutGeneralFormButtons->setEnabled(true);
            ui->backButton->setVisible(true);
            ui->CanselButton->setVisible(true);
            ui->NextButton->setVisible(true);
            ui->LayoutNumber2->setEnabled(true);
            ui->gridLayout_2->setEnabled(true);
            ui->TreeWidget->setVisible(true);
            ui->pushButtonRemoveAll->setVisible(true);
            ui->pushButtonSelectAll->setVisible(true);

            //не видимые элементы
            ui->LayoutProgresBar->setEnabled(false);
            ui->ProgressBar->setVisible(false);
            ui->ProgressLabel->setVisible(false);
            ui->LayoutQuestion->setEnabled(false);
            ui->radioButtonCustomUpdate->setVisible(false);
            ui->radioButtonExitFromUpdate->setVisible(false);
            ui->radioButtonStandartUpdate->setVisible(false);
        }
        break;
        case 3:
        {
            //видимые элементы
            ui->LayoutGeneralFormButtons->setEnabled(true);
            ui->CanselButton->setVisible(true);
            ui->NextButton->setVisible(true);
            ui->LayoutProgresBar->setEnabled(true);
            ui->ProgressBar->setVisible(true);
            ui->ProgressLabel->setVisible(true);
            ui->NextButton->setText("Finish");

            //не видимые элементы
            ui->backButton->setVisible(false);
            ui->LayoutNumber2->setEnabled(false);
            ui->gridLayout_2->setEnabled(false);
            ui->TreeWidget->setVisible(false);
            ui->pushButtonRemoveAll->setVisible(false);
            ui->pushButtonSelectAll->setVisible(false);
            ui->LayoutQuestion->setEnabled(false);
            ui->radioButtonCustomUpdate->setVisible(false);
            ui->radioButtonExitFromUpdate->setVisible(false);
            ui->radioButtonStandartUpdate->setVisible(false);

        }
        break;
        default:
        {
            //видимые элементы
            ui->LayoutGeneralFormButtons->setEnabled(true);
            ui->backButton->setVisible(true);
            ui->CanselButton->setVisible(true);
            ui->NextButton->setVisible(true);
            ui->LayoutQuestion->setEnabled(true);
            ui->radioButtonCustomUpdate->setVisible(true);
            ui->radioButtonExitFromUpdate->setVisible(true);
            ui->radioButtonStandartUpdate->setVisible(true);

            //не видимые элементы
            ui->LayoutNumber2->setEnabled(false);
            ui->gridLayout_2->setEnabled(false);
            ui->TreeWidget->setVisible(false);
            ui->pushButtonRemoveAll->setVisible(false);
            ui->pushButtonSelectAll->setVisible(false);
            ui->LayoutProgresBar->setEnabled(false);
            ui->ProgressBar->setValue(false);
            ui->ProgressLabel->setVisible(false);
        }
        break;
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_CanselButton_clicked()
{
    if(ShowMessage(QString("Are you sure what you want to complete the update program?")))
    {
        close();
    }
    else
    {
        return;
    }
}

void Dialog::on_NextButton_clicked()
{
    switch(m_currentPage)
    {
        case 1:
        {
            if(ui->radioButtonCustomUpdate->isChecked())
            {
                m_currentPage = 2;
                setCurentPage(m_currentPage);
            }
            if(ui->radioButtonExitFromUpdate->isChecked())
            {
                on_CanselButton_clicked();
            }
            if(ui->radioButtonStandartUpdate->isChecked())
            {
                m_currentPage = 3;
                setCurentPage(m_currentPage);
                m_Controller->DownloadUpdates(ui->ProgressLabel,ui->ProgressBar);
            }
            if(!ui->radioButtonCustomUpdate->isChecked() && !ui->radioButtonExitFromUpdate->isChecked() && !ui->radioButtonStandartUpdate->isChecked())
            {
                return;
            }
        }
        break;
        case 2:
        {
            m_currentPage = 3;
            setCurentPage(m_currentPage);
            m_Controller->reLoadUpdateList();
            m_Controller->DownloadUpdates(ui->ProgressLabel,ui->ProgressBar);
        }
        break;
        case 3:
        {
            if(!m_Controller->filesAlreadyDownloaded())
            {
                QMessageBox::information(0,"Downloading files!!!","Files are downloaded, finish updating is impossible!!!");
                return;
            }

            close();
        }
        break;
        default :
        {
            return;
        }
        break;
    }

}

void Dialog::on_backButton_clicked()
{
    if(m_currentPage == 1)
    {
        return;
    }
    if(m_currentPage == 2)
    {
        m_currentPage = 1;
        setCurentPage(m_currentPage);
    }
    if(m_currentPage == 3)
    {
        return;
    }

}

void Dialog::on_pushButtonSelectAll_clicked()
{
    m_Controller->SelectAllItems();
}

void Dialog::on_pushButtonRemoveAll_clicked()
{
    m_Controller->RemoveAllItems();
}

void Dialog::onItemClicked(QTreeWidgetItem* item, int val)
{
    qDebug()<<val;
    if(static_cast<QString>(item->text(0))==QString("Update program"))
        return;
    if(static_cast<QString>(item->parent()->text(0))==QString("Update program"))
        return;
    if(item->childCount()!=0)
    {
        for(int i=0;i<item->childCount();i++)
        {
               item->child(i)->setCheckState(val,item->checkState(val));
        }
    }
    else
    {
        item->parent()->setCheckState(0,Qt::PartiallyChecked);

    }
}


bool Dialog::ShowMessage(QString value)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Update program");
    msgBox.setText("Update program informaton");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setInformativeText(value);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch (ret)
    {
        case QMessageBox::Cancel:
            return false;
        break;
        case QMessageBox::Ok:
            return true;
        break;
        default:
            return false;
        break;
     }
}

