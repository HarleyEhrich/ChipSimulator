#include "LogHandler.h"

LogHandlerPrivate::LogHandlerPrivate() {

    logDir.setPath(LOG_FILE_DIR);

    QString logFilePath = logDir.absoluteFilePath("today.log"); // 获取日志的路径
    logFileCreatedDate = QFileInfo(logFilePath).lastModified().date();

    // 打开日志文件，如果不是当天创建的，备份已有日志文件
    openAndBackupLogFile();

    // 十分钟检查一次日志文件创建时间
    renameLogFileTimer.setInterval(1000 *  2);
    renameLogFileTimer.start();

    //
    QObject::connect(&renameLogFileTimer,
            &QTimer::timeout,

            [this](){
        QMutexLocker locker(&LogHandlerPrivate::_logMutex);
        openAndBackupLogFile(); // 打开日志文件
        checkLogFiles(); // 检测当前日志文件大小
        autoDeleteLog(); // 自动删除30天前的日志
    });

    // 定时刷新日志输出到文件，尽快的能在日志文件里看到最新的日志
    flushLogFileTimer.setInterval(1000);
    flushLogFileTimer.start();
    QObject::connect(&flushLogFileTimer, &QTimer::timeout, [] {
        QMutexLocker locker(&LogHandlerPrivate::_logMutex);
        if (nullptr != logOut) {
            logOut->flush();
        }
    });

}

LogHandlerPrivate::~LogHandlerPrivate() {
    if (nullptr != logFile) {
        logFile->flush();
        logFile->close();
        delete logOut;
        delete logFile;

        // 因为他们是 static 变量
        logOut  = nullptr;
        logFile = nullptr;
    }
}

// 打开日志文件 log.txt，如果不是当天创建的，则使用创建日期把其重命名为 yyyy-MM-dd.log，并重新创建一个 log.txt
void LogHandlerPrivate::openAndBackupLogFile() {
    // 总体逻辑:
    // 1. 程序启动时 logFile 为 nullptr，初始化 logFile，有可能是同一天打开已经存在的 logFile，所以使用 Append 模式
    // 2. logFileCreatedDate is nullptr, 说明日志文件在程序开始时不存在，所以记录下创建时间
    // 3. 程序运行时检查如果 logFile 的创建日期和当前日期不相等，则使用它的创建日期重命名，然后再生成一个新的 log.txt 文件
    // 4. 检查日志文件超过 LOGLIMIT_NUM 个，删除最早的
    // 备注：log.txt 始终为当天的日志文件，当第二天，会执行第3步，将使用 log.txt 的创建日期重命名它


    // 如果日志所在目录不存在，则创建
    if (!logDir.exists()) {
        logDir.mkpath("."); // 可以递归的创建文件夹
    }
    QString logFilePath = logDir.absoluteFilePath("today.log"); // log.txt的路径


    if (logFile == nullptr) {
        //初始化Log文件
        logFile = new QFile(logFilePath);

        //如果存在日志文件，将日志文件内容附加到textstream
        logOut  = (logFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) ?  new QTextStream(logFile) : nullptr;

        if (logOut != nullptr){
            //初始化文件text stream
            logOut->setEncoding(QStringConverter::Encoding::Utf8);
        }

        // [[2]] 如果文件是第一次创建，则创建日期是无效的，把其设置为当前日期
        if (logFileCreatedDate.isNull()) {
            logFileCreatedDate = QDate::currentDate();
        }
    }

    // [[3]] 程序运行时如果创建日期不是当前日期，则使用创建日期重命名，并生成一个新的 log.txt
    if (logFileCreatedDate != QDate::currentDate()) {
        logFile->flush();
        logFile->close();
        delete logOut;
        delete logFile;

        QString newLogPath = logDir.absoluteFilePath(logFileCreatedDate.toString("yyyy-MM-dd.log"));;
        QFile::copy(logFilePath, newLogPath); // Bug: 按理说 rename 会更合适，但是 rename 时最后一个文件总是显示不出来，需要 killall Finder 后才出现
        QFile::remove(logFilePath); // 删除重新创建，改变创建时间

        // 重新创建 log.txt
        logFile = new QFile(logFilePath);
        logOut  = (logFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) ?  new QTextStream(logFile) : nullptr;
        logFileCreatedDate = QDate::currentDate();
        if (logOut != nullptr){
            logOut->setEncoding(QStringConverter::Encoding::Utf8);
        }

    }
}

// 检测当前日志文件大小
void LogHandlerPrivate::checkLogFiles() {
    // 如果 protocal.log 文件大小超过5M，重新创建一个日志文件，原文件存档为yyyy-MM-dd_hhmmss.log
    if (logFile->size() > 1024*g_logLimitSize) {
        logFile->flush();
        logFile->close();
        delete logOut;
        delete logFile;

        QString logPath = logDir.absoluteFilePath("today.log"); // 日志的路径
        QString newLogPath = logDir.absoluteFilePath(logFileCreatedDate.toString("yyyy-MM-dd.log"));
        QFile::copy(logPath, newLogPath); // Bug: 按理说 rename 会更合适，但是 rename 时最后一个文件总是显示不出来，需要 killall Finder 后才出现
        QFile::remove(logPath); // 删除重新创建，改变创建时间

        logFile = new QFile(logPath);
        logOut  = (logFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) ?  new QTextStream(logFile) : NULL;
        logFileCreatedDate = QDate::currentDate();
        if (logOut != nullptr)
            logOut->setEncoding(QStringConverter::Encoding::Utf8);
    }
}

// 自动删除30天前的日志
void LogHandlerPrivate::autoDeleteLog()
{
    QDateTime now = QDateTime::currentDateTime();

    // 前30天
    QDateTime dateTime1 = now.addDays(-30);
    QDateTime dateTime2;

    QString logPath = logDir.absoluteFilePath("today.log"); // 日志的路径
    QDir dir(logPath);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo f, fileList ) {
        // "."和".."跳过
        if (f.baseName() == "")
            continue;

        dateTime2 = QDateTime::fromString(f.baseName(), "yyyy-MM-dd");
        if (dateTime2 < dateTime1) { // 只要日志时间小于前30天的时间就删除
            dir.remove(f.absoluteFilePath());
        }
    }
}

// 消息处理函数
void LogHandlerPrivate::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QMutexLocker locker(&LogHandlerPrivate::_logMutex);

    QString level;
    switch (type) {
    case QtDebugMsg:
        level = "Debug";
        break;
    case QtInfoMsg:
        level = "Info";
        break;
    case QtWarningMsg:
        level = "Warning";
        break;
    case QtCriticalMsg:
        level = "Error";
        break;
    case QtFatalMsg:
        level = "Fatal";
        break;
    default:
        break;
    }

    if (nullptr == LogHandlerPrivate::logOut) {
        return;
    }

    // 输出到日志文件, 格式: 时间 - [Level] (文件名:行数, 函数): 消息
    QString fileName = context.file;
    int index = fileName.lastIndexOf(QDir::separator());
    fileName = fileName.mid(index + 1);

    (*LogHandlerPrivate::logOut) << QString("%1-[%2]{%3:%4, %5}: %6\n")
                                        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),level,fileName)
                                        .arg(context.line)
                                        .arg(context.function,msg);
}




LogHandler::LogHandler() : d(nullptr) {

}

// 安装消息处理函数
void LogHandler::installMessageHandler() {
    QMutexLocker locker(&LogHandlerPrivate::_logMutex);

    if (nullptr == d) {
        d = new LogHandlerPrivate();
        qInstallMessageHandler(LogHandlerPrivate::messageHandler);
    }
}

// 卸载消息处理函数并释放资源
void LogHandler::uninstallMessageHandler() {
    QMutexLocker locker(&LogHandlerPrivate::_logMutex);

    qInstallMessageHandler(nullptr);
    delete d;
    d = nullptr;
}
