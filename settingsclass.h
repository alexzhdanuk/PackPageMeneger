#include <QString>
#include <QStringList>
#ifndef OptionsClass_H
#define OptionsClass_H
class OptionsClass
{
public:
    OptionsClass(){m_localProgramVersion = 0; m_updateVersion = 0; m_serverAdress = "";}
    int getLocalProgramVersion(){return m_localProgramVersion;}
    int getUpdateVersion(){return m_updateVersion;}
    QString getServerAdress(){return m_serverAdress;}
    QStringList getFileList(){return m_fileList;}
    QString getProgramPath(){return m_curentDerectory;}
    QString getUrlAdressProgram(){return m_urlProgram;}
    QStringList getUrlAdressPatterns(){return m_urlPatterns;}
    QString getLogin(){return m_login;}
    QString getPass(){return m_pass;}
    QStringList getDelList(){return m_listDelFiles;}
    QString getAbsPath(){return m_absPath;}
    QString getFtpServer(){return m_ftpServer;}

public:
    void setLocalProgramVersion(int value){m_localProgramVersion = value;}
    void setUpdateVersion(int value){m_updateVersion = value;}
    void setServerAdress(QString value){m_serverAdress = value;}
    void setFileList(QStringList list){m_fileList = list;}
    void setProgramPath(QString value){m_curentDerectory = value;}
    void setUrlAdresProgram(QString value){m_urlProgram = value;}
    void setUrlAdresPatterns(QStringList value){m_urlPatterns = value;}
    void setLogin(QString value){m_login = value;}
    void setPass(QString value){m_pass = value;}
    void setDelList(QStringList value){m_listDelFiles = value;}
    void setAbsPath(QString value){m_absPath = value;}
    void setFtpserver(QString value){m_ftpServer = value;}

private:
    int m_localProgramVersion;
    int m_updateVersion;
    QString m_serverAdress;
    QStringList m_fileList;
    QString m_curentDerectory;
    QString m_urlProgram;
    QStringList m_urlPatterns;
    QString m_login;
    QString m_pass;
    QStringList m_listDelFiles;
    QString m_absPath;
    QString m_ftpServer;

};
#endif //OptionsClass_H



#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H

class SettingsClass
{
public:
    SettingsClass();

public: bool loadSettings();
public: bool saveSettings();
public: bool getChanceDeleteFileOrDir(QString &value);

public: OptionsClass m_Options;

private: QString m_filePath;

};

#endif // SETTINGSCLASS_H

