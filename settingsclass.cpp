#include "settingsclass.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

SettingsClass::SettingsClass()
{

    m_Options.setLocalProgramVersion(10);
    m_Options.setServerAdress("http://sms-feed.apricus.pp.ua/FotobookUpdate/test.php");
    m_Options.setUpdateVersion(200);
    m_filePath = "settings.ini";
    QStringList list;
    m_Options.setFileList(list);
    m_Options.setLogin("zmey");
    m_Options.setPass("14101989");
    m_Options.setFtpserver("sms-feed.apricus.pp.ua");
    m_Options.setUrlAdresProgram("Photobook.exe");
    m_Options.setProgramPath("./www/sms-feed.apricus.pp.ua/fotobook");
    m_Options.setAbsPath("./www/sms-feed.apricus.pp.ua/fotobook");
    list.clear();
    list <<"ssssss.sb";

    m_Options.setUrlAdresPatterns(list);
}

bool SettingsClass::loadSettings()
{
    QFile file(m_filePath);
    if(file.open(QIODevice::ReadWrite))
    {
        QString server,path,program;
        QStringList list1,list2;
        int programVersion,updateVersion;
        QDataStream in(&file);
        in >> programVersion >> server >> updateVersion >> list1 >> path >> program >> list2;
        m_Options.setLocalProgramVersion(programVersion);
        m_Options.setServerAdress(server);
        m_Options.setUpdateVersion(updateVersion);
        m_Options.setFileList(list1);
        m_Options.setProgramPath(path);
        m_Options.setUrlAdresProgram(program);
        m_Options.setUrlAdresPatterns(list2);
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
            << m_Options.getFileList()
            << m_Options.getProgramPath()
            << m_Options.getUrlAdressProgram()
            << m_Options.getUrlAdressPatterns();
    }

    file.close();
    return true;

}

bool SettingsClass::getChanceDeleteFileOrDir(QString &value)
{
    bool state = true;
    foreach(QString str, m_Options.getFileList())
    {
        if(str == value) state = false;
    }

    return state;
}
