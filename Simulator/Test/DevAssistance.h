#ifndef DEVASSISTANCE_H
#define DEVASSISTANCE_H
/**
*    @file:    developmentassistance.h
*    @brief:   用于开发辅助类，全局唯一实例，可以通过调用该实例来完成一些快速辅助功能
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-03-30  01:34
*/

#include <QObject>
#include <QString>
#include <QDebug>

class DevelopmentAssistance;

typedef std::weak_ptr<DevelopmentAssistance> DevelopmentAssistancePtr;
#define DAMsg(msgStatment) DevelopmentAssistance::getDAInstance()->sendDebugMsg(msgStatment);

class DevelopmentAssistance : public QObject
{
    Q_OBJECT

signals:
    void debugMsg(QString msg);
public:
    static DevelopmentAssistancePtr getDAInstance(){
        return DevelopmentAssistancePtr{__assistSharedPtr};
    }

    void sendDebugMsg(QString msg){
        emit debugMsg(msg);
    }

    QString& operator()(QString& msg){
        qDebug()<<msg;
    }

    void operator <<(const QString& str){
        qDebug()<<str;
    }

    explicit DevelopmentAssistance(QObject *parent = nullptr);

private:
    QString __storedMsg;

private:


    static std::shared_ptr<DevelopmentAssistance> __assistSharedPtr;


};

#endif // DEVASSISTANCE_H
