#ifndef CONTROLERCLASS_H
#define CONTROLERCLASS_H

#include <QObject>
#include "settingsclass.h"
#include "FtpDownload.h"
#include <QTreeWidget>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QFile>
#include <QLabel>
#include <QProgressBar>

class ControlerClass : public QObject
{
    Q_OBJECT
public:
    explicit ControlerClass(QObject *parent = 0,const QString &programPath="");

public:
    void setupStartOptions(QTreeWidget*);
    void DownloadUpdates(QLabel* label, QProgressBar* bar);
    void SelectAllItems();
    void RemoveAllItems();
    void reLoadUpdateList();
    bool filesAlreadyDownloaded(){return allFilesDownload;}

private:
    void RemoveProgram();
    void addDataToTreeWidget(QTreeWidget*);
    void SendCommand(const QString &command);
    void downloadFile();


signals:
    void closeProgram();


public slots:
    void ansverServerSlot(QNetworkReply* reply);
    void onTimer();
    void parseString(const QString &val);

private:
    FtpDownload m_FtpDownloader;
    SettingsClass* m_Settings;
    QTreeWidget* m_QTreeWidget;
    QNetworkReply *mreply;
    QNetworkAccessManager* nam;
    QUrl baseurl;
    bool isUpdated;
    QTimer *timer;
    int m_curentDownload;
    bool isDowloadProgram;
    QFile* file;
    QList<QTreeWidgetItem* > list;
    QString m_curentCommand;
    bool m_xmlFileIsSave;
    QLabel* m_progresLabel;
    QProgressBar* m_progresBar;
    QStringList m_downloadList;
    int m_curentDownloadFile;
    bool allFilesDownload;
};

#endif // CONTROLERCLASS_H
