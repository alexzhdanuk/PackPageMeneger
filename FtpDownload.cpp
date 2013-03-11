#include <QtNetwork>
#include <QDebug>
#include "FtpDownload.h"
#include <QMessageBox>

FtpDownload::FtpDownload(QObject *parent) : QObject(parent)
{
    ftp = new QFtp();
    ftp->setTransferMode(QFtp::Active);
    connect(ftp, SIGNAL(commandFinished(int,bool)),this, SLOT(FtpFinished(int,bool)));
    connect(ftp, SIGNAL(done(bool)),this,SLOT(FinishedDownload(bool)));
    connect(ftp,SIGNAL(dataTransferProgress(qint64,qint64)),this,SLOT(FtpdataTransferProgress(qint64,qint64)));
    isConected = false;
}

void FtpDownload::connectToServer(QString server,QString login,QString pass)
{
    this->m_server = server;
    this->m_pass = pass;
    this->m_login = login;

}

void FtpDownload::downloadFile(QString fileName, QString curPath)
{
    ftp->connectToHost(m_server,21);

    ftp->login(m_login,m_pass);
    totalDownload = 0;

    qDebug()<< fileName << curPath <<" ---ftp";

    file = new QFile(fileName);

    if(file->open(QIODevice::WriteOnly))
    {

        ftp->cd(QString(curPath));
        ftp->get(QString(fileName),file);
        fileIsDownload = false;
    }
    else
    {
        switch(file->error())
        {
            case QFile::OpenError:
            {
            QMessageBox::information(0,"",file->errorString());
                break;
            }
            default:
            {
            qDebug()<<file->error();
            break;
            }
        }
    }
}

void FtpDownload::FtpFinished(int val,bool state)
{
    if(state)
    {
        QString error;
        error = ftp->errorString().replace("\n", " ");
        qDebug()<<error;

    }

    if(ftp->currentCommand()==QFtp::Connected)
    {
        isConected = true;
        qDebug()<<"conected";
    }

    if(ftp->currentCommand()==QFtp::Cd)
    {
        qDebug()<<"cd";
    }

    if(ftp->currentCommand()==QFtp::Get)
    {
        file->flush();
        file->close();
        ftp->close();
        fileIsDownload = true;
        qDebug()<<"file is dowload";
    }
}




void FtpDownload::disconectFromServer()
{
    ftp->close();
}


void FtpDownload::FinishedDownload(bool hasError)
{
    if(hasError)
       {
          QString error;
          switch(ftp->error())
          {
             case QFtp::HostNotFound:
             {
                error = "не удалось обнаружить адрес";
                break;
             }
             default:
             {
                error = ftp->errorString().replace("\n", " "); // errorString() часто содержит \n
                break;
             }
          }
          qDebug()<<error;
        }
}

void FtpDownload::FtpdataTransferProgress(qint64 bytesRead, qint64 totalBytes)
{
   totalDownload = bytesRead;
   maxDownload = totalBytes;
}
