#include "dialog.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *cyrillicCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(cyrillicCodec);
    QTextCodec::setCodecForLocale(cyrillicCodec);
    QTextCodec::setCodecForCStrings(cyrillicCodec);

    #if defined(Q_WS_WIN32)
        Dialog w(0,a.applicationDirPath());
    #elif defined(Q_WS_MAC)
        Dialog* w(0,a.applicationDirPath());
    #endif
    w.show();
    
    return a.exec();
}
