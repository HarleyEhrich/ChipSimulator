#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "Log/LogHandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // [[1]] 安装消息处理函数
//    LogHandler::Get().installMessageHandler();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "AmtlSimulator_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();



    return a.exec();
}
