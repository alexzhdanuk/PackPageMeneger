#ifndef HttpDownload_H
#define HttpDownload_H

#include <QUrl>
#include <QFtp>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QFile;
class QNetworkReply;
QT_END_NAMESPACE

class FtpDownload : public QObject
{
    Q_OBJECT

public:
    FtpDownload(QObject *parent = 0);
    void downloadFile(QString fileName,QString curPath ,QString directory = "");
    void connectToServer(QString server,QString login,QString pass);
    void disconectFromServer();



private slots:

    void FtpFinished(int,bool);
    void FinishedDownload(bool);
    void FtpdataTransferProgress(qint64,qint64);


public:
    QStringList  listDirectory;
    bool fileIsDownload;
    bool isConected;
    int totalDownload;
    int maxDownload;

private:
    QFtp* ftp;
    QFile *file;
    bool httpRequestAborted;
    QString m_login;
    QString m_pass;
    QString m_server;





};

#endif
