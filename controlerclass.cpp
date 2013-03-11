#include "controlerclass.h"
#include <QMessageBox>
#include <QDebug>
#include "QXmlStreamReader"
#include <QTreeWidgetItem>
#include <QDomDocument>

#define XML_FILE_NAME "1.xml"

ControlerClass::ControlerClass(QObject *parent,const QString &programPath) :
    QObject(parent),m_FtpDownloader()
{
        m_Settings = new SettingsClass();
        nam = new QNetworkAccessManager();
        isUpdated = false;
        //m_Settings->saveSettings();
        //m_Settings->loadSettings();
        m_Settings->m_Options.setProgramPath(programPath);
        timer = new QTimer(this);
        m_curentDownload = 0;
        isDowloadProgram = false;
        m_xmlFileIsSave = false;
        allFilesDownload = false;



        connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
        connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(ansverServerSlot(QNetworkReply*)));

}

void ControlerClass::setupStartOptions(QTreeWidget* widget)
{
    m_curentCommand = "version";
    SendCommand(m_curentCommand);
    m_QTreeWidget = widget;

}

void ControlerClass::SendCommand(const QString &command)
{
    QUrl mpost;
    mpost.addQueryItem("command",command);
    QNetworkRequest request(QUrl(m_Settings->m_Options.getServerAdress()));
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader,mpost.encodedQuery().size());

    mreply = nam->post(request, mpost.encodedQuery());
}


void ControlerClass::onTimer()
{
    int all_files = m_downloadList.count()+1;
    QString str = QString::number(m_curentDownload+1);
    str+="/";
    str+=QString::number(all_files);
    m_progresLabel->setText(str);
    m_progresBar->setRange(0,m_FtpDownloader.maxDownload);
    m_progresBar->setValue(m_FtpDownloader.totalDownload);

    if(m_FtpDownloader.fileIsDownload)
    {
        timer->stop();
        //if(isDowloadProgram) m_curentDownload++;
        isDowloadProgram = true;
        downloadFile();
    }

}


void ControlerClass::ansverServerSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString string = QString::fromUtf8(bytes.data());

        parseString(string);

        qDebug()<<m_Settings->m_Options.getUpdateVersion();
        if(m_Settings->m_Options.getUpdateVersion() > m_Settings->m_Options.getLocalProgramVersion())
        {
            isUpdated = true;
        }
        else
        {
            QMessageBox::information(0,"Information",QString("Your software is correct at the time of danniy!!!"));
        }
    }
    else
    {
         qDebug() << reply->errorString();
         emit closeProgram();
    }

}

void ControlerClass::parseString(const QString &val)
{
        QFile file(XML_FILE_NAME);
        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream st(&file);
            st << val;
            file.close();
            addDataToTreeWidget(m_QTreeWidget);
        }
        else
        {
            QMessageBox::information(0,"Error","File is not open");
            emit closeProgram();
        }
}

void ControlerClass::addDataToTreeWidget(QTreeWidget* widget)
{
    QFile file(XML_FILE_NAME);
    QDomDocument doc;

    if(file.open(QIODevice::ReadOnly))
    {
        doc.setContent(&file);
        QTreeWidgetItem* itemUp = new QTreeWidgetItem();
        itemUp->setText(0,"Update program");
        QTreeWidgetItem* childItemUp = new QTreeWidgetItem();
        childItemUp->setText(0,doc.elementsByTagName("version").at(0).toElement().text());
        m_Settings->m_Options.setUpdateVersion(doc.elementsByTagName("version").at(0).toElement().text().toInt());
        itemUp->addChild(childItemUp);
        list << itemUp;
        QTreeWidgetItem* generalItem = new QTreeWidgetItem();
        generalItem->setText(0,doc.elementsByTagName("Patterns").at(0).toElement().attribute("name"));

        QDomNodeList groups = doc.elementsByTagName("Patterns").at(0).childNodes();

        for(int i = 0;i<groups.count();i++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0,groups.at(i).toElement().attribute("name"));

            for(int j = 0;j<groups.at(i).childNodes().count();j++)
            {
                QDomNode value = groups.at(i).childNodes().at(j);
                QTreeWidgetItem* childItem = new QTreeWidgetItem();
                m_downloadList << value.toElement().text();
                childItem->setText(0,value.toElement().text());
                childItem->setCheckState(0,Qt::Unchecked);
                item->addChild(childItem);
            }

            item->setCheckState(0,Qt::PartiallyChecked);
            generalItem->addChild(item);
        }
        list<<generalItem;
        file.close();
    }
    widget->addTopLevelItems(list);
}

void ControlerClass::DownloadUpdates(QLabel *label, QProgressBar *bar)
{
    RemoveProgram();
    m_progresLabel = label;
    m_progresBar = bar;
    m_FtpDownloader.connectToServer(m_Settings->m_Options.getFtpServer(),m_Settings->m_Options.getLogin(),m_Settings->m_Options.getPass());
    downloadFile();
}

void ControlerClass::downloadFile()
{
    if(m_curentDownload == m_downloadList.count())
       {
           allFilesDownload = true;
           m_Settings->m_Options.setLocalProgramVersion(m_Settings->m_Options.getUpdateVersion());
           m_Settings->saveSettings();
           return;
       }


       if(!isDowloadProgram)
       {
           qDebug()<<m_Settings->m_Options.getUrlAdressProgram() << m_Settings->m_Options.getProgramPath();
           m_FtpDownloader.downloadFile(m_Settings->m_Options.getUrlAdressProgram(),m_Settings->m_Options.getAbsPath());
           timer->start(1);
           isDowloadProgram = true;
           return;

       }

       m_FtpDownloader.downloadFile(m_downloadList.at(m_curentDownload),m_Settings->m_Options.getAbsPath(),"/tamplates/");
       m_curentDownload++;
       timer->start(1);

}

void ControlerClass::SelectAllItems()
{
    foreach(QTreeWidgetItem* item,list)
    {
        if(static_cast<QString>(item->text(0))==QString("Update program"))
            continue;
        if(item->childCount()==0)
            continue;
        for(int i=0;i<item->childCount();i++)
        {
            QTreeWidgetItem* childItem = item->child(i);
            childItem->setCheckState(0,Qt::Checked);
            if(childItem->childCount()==0)
                continue;
            for(int j=0;j<childItem->childCount();j++)
            {
                QTreeWidgetItem* ChildChildItem = childItem->child(j);
                ChildChildItem->setCheckState(0,Qt::Checked);
            }
        }
    }
 }

void ControlerClass::RemoveAllItems()
{
    foreach(QTreeWidgetItem* item,list)
    {
        if(static_cast<QString>(item->text(0))==QString("Update program"))
            continue;
        if(item->childCount()==0)
            continue;
        for(int i=0;i<item->childCount();i++)
        {
            QTreeWidgetItem* childItem = item->child(i);
            childItem->setCheckState(0,Qt::Unchecked);
            if(childItem->childCount()==0)
                continue;
            for(int j=0;j<childItem->childCount();j++)
            {
                QTreeWidgetItem* ChildChildItem = childItem->child(j);
                ChildChildItem->setCheckState(0,Qt::Unchecked);
            }
        }
    }
}

void ControlerClass::reLoadUpdateList()
{
    m_downloadList.clear();
    foreach(QTreeWidgetItem* item,list)
    {
        if(static_cast<QString>(item->text(0))==QString("Update program"))
            continue;
        if(item->childCount()==0)
            continue;
        for(int i=0;i<item->childCount();i++)
        {
            QTreeWidgetItem* childItem = item->child(i);
            if(childItem->childCount()==0)
                continue;
            for(int j=0;j<childItem->childCount();j++)
            {
                QTreeWidgetItem* ChildChildItem = childItem->child(j);
                if(ChildChildItem->checkState(0)==Qt::Checked)
                    m_downloadList << ChildChildItem->text(0);
            }
        }
    }

}

void ControlerClass::RemoveProgram()
{
    QStringList list;

    list = m_Settings->m_Options.getDelList();
    foreach(QString str,list)
    {
        QFile(m_Settings->m_Options.getProgramPath()+"/"+str).remove();
    }

}
