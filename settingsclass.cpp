#include "settingsclass.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

SettingsClass::SettingsClass()
{

    QStringList list;
    m_filePath = "settings.ini";

    m_Options.setLocalProgramVersion(10);
    m_Options.setServerAdress("http://sms-feed.apricus.pp.ua/FotobookUpdate/test.php");
    m_Options.setUpdateVersion(200);
    m_Options.setLogin("zmey");
    m_Options.setPass("14101989");
    m_Options.setFtpServer("sms-feed.apricus.pp.ua");
    m_Options.setUrlAdresProgram("index.php");
    m_Options.setProgramPath("./www/sms-feed.apricus.pp.ua/fotobook");
    m_Options.setAbsPath("./www/sms-feed.apricus.pp.ua/fotobook");

    list.clear();
    list <<"ssssss.sb";

    m_Options.setUrlAdresPatterns(list);
    list.clear();
    list << "index.php";
    m_Options.setDelList(list);
    loadSettings();
}

bool SettingsClass::loadSettings()
{
    QFile file(m_filePath);

    if (!QFile::exists(m_filePath))

        return false;
    if(file.open(QIODevice::ReadWrite))
    {
        QString server,path,absPath,urlAdrProgram,login,pass,FtpServer;
        QStringList listPat, listDel;
        int programVersion,updateVersion;
        QDataStream in(&file);
        //in >> m_Options;


        in >> programVersion
           >> server
           >> updateVersion
           >> login
           >> pass
           >> FtpServer
           >> urlAdrProgram
           >> path
           >> absPath
           >> listPat
           >> listDel;

        m_Options.setLocalProgramVersion(programVersion);
        m_Options.setServerAdress(server);
        m_Options.setUpdateVersion(updateVersion);
        m_Options.setLogin(login);
        m_Options.setPass(pass);
        m_Options.setFtpServer(FtpServer);
        m_Options.setUrlAdresProgram(urlAdrProgram);
        m_Options.setProgramPath(path);
        m_Options.setAbsPath(absPath);
        m_Options.setUrlAdresPatterns(listPat);
        m_Options.setDelList(listDel);


    }
    file.close();
    return true;
}

bool SettingsClass::saveSettings()
{
    QFile file(m_filePath);
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QDataStream out(&file);
        out << m_Options.getLocalProgramVersion()
            << m_Options.getServerAdress()
            << m_Options.getUpdateVersion()
            << m_Options.getLogin()
            << m_Options.getPass()
            << m_Options.getFtpServer()
            << m_Options.getUrlAdressProgram()
            << m_Options.getProgramPath()
            << m_Options.getAbsPath()
            << m_Options.getUrlAdressPatterns()
            << m_Options.getDelList();
    }

    file.close();
    return true;

}

