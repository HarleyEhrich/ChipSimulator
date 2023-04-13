#ifndef ABSTRACTCONINTERFACE_H
#define ABSTRACTCONINTERFACE_H

#include "AbstractConInterface_global.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPixmap>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <QVector>
#include <QWidget>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace AMTL {
    enum MSGTYPE{DEAFAULT,WARNING,ERROR};
}

class ABSTRACTCONINTERFACE_EXPORT AbstractConInterface : public QObject ,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

signals:
    //日志发送入口
    void newLog(const QString& senderMsg, const QString& msg, AMTL::MSGTYPE msgType);

    //显示新的窗口
    void newPannelWidget(const QString& senderMsg, const QString& pannelTitle, QWidget* pannel);

public:
    explicit AbstractConInterface(QGraphicsItem *parent = nullptr);

    //Function which can be override by all kinds of plugin
public slots:
    //创建接口，返回该实例
    virtual AbstractConInterface* creat(long sceneId) =0 ;

    //运行函数，使用run来统一管理控件状态的更新入口，对外界传递该函数来使该控件可被其它控件调用，每次调用必须根据此完成状态更新
    virtual void run()=0;

    //运行保存，读取机制，通过将控件状态转为文本，以供下次读取，注意到图元基本信息，诸如位置等应有Abstarct 接口完成，理论上不推荐自主实现，但是也可以自主实现
    virtual bool loadStatusFormText(const QString& text) = 0;
    virtual bool saveStatusToText(QString& text) = 0;

    //获取控件的设置控件组，主界面处理控件删除后设置控件的删除，不需要控件自行处理。
    virtual QVector<QWidget*> getSetWidgetsVec() = 0;

    //获取控件设置面板，控件每次需要创建示例，注意到不应当管理创建之后的控件生存周期的管理，主界面将会处理。
    virtual QWidget* getSettingPannel() = 0;


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    // Basic un-override function
public:
    //基本信息设置
    bool isIntial();

    const QString& getConIid();

    const QString& getCreatTime();

    const QString& getConName();

    const QString& getAuthor();

    const QString& getConImgaePath();
    const QPixmap& getConImage();

    const QString& getConDescribe();

    //从文本内加载控件信息
    bool loadFromTextAbstract(const QString& abText);

    //将文本信息加载到控件内
    bool saveToTextAbstract(QString& abText);

    bool isMoveable() const;
    void setIsMoveable(bool newIsMoveable);

    long sceneId() const;
    void setSceneId(long newScenceId);

private:
    bool innitial(const QString& creatTime,const QString& author,const QString& conName, const QString& conImagePath=":/default _electronic_component.png");

private:
    //是否初始化，未初始化不允许加载入。
    bool _isInitial=false;

    //控件唯一标识，反射时将使用该标识来创建实例对象
    QString _conId;
    QString _conDescribeInfo;

    QString _creatTime;
    QString _author;
    QString _conName;
    QString _conImagePath;
    QPixmap _conImage;

    //控件别名
    QString _conNickName;

    //控件设置
    long _sceneId=-1;

    //是否可移动--默认可移动
    bool _isMoveable=true;

    //鼠标处于按下状态
    bool _mousePressed=false;

    //鼠标点击事件发生点
    QPointF _mousePressedPoint;

};

//    //注册设置按钮，提供按钮名称，以及对应的设置函数，注意到该函数仅能接收到点击事件产生的true，false，两个值
//    bool registerSetBtn(const QString& btnName,std::function<void(int)> setFunction, bool btndefaultValue=false);
//    bool registerSetValueBox(const QString& valueName, std::function<void(int)> setFunction, int defaultValue=0);


#define AbstractConInterface_iid "com.amtl.plugin.abstractconinterface"
Q_DECLARE_INTERFACE(AbstractConInterface, AbstractConInterface_iid)

#endif // ABSTRACTCONINTERFACE_H
