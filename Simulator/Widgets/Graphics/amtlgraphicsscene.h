#ifndef AMTLGRAPHICSSCENE_H
#define AMTLGRAPHICSSCENE_H

/**
*    @file:    AmtlGraphicsScene.h
*    @brief:   场景-注意不准包含loader
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-05-18  15:00
*/

#include <QDebug>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMap>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QPolygonF>
#include <QRectF>
#include <QTimer>
#include <QWeakPointer>

#include <abstractconinterface.h>

#include "Include/ProjectInclude.h"

class AmtlGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AmtlGraphicsScene(QObject *parent = nullptr);

    virtual ~AmtlGraphicsScene();

    //Sig and slots
signals:
    void requestToastInfo(QString infoTitle,
                          QString info,
                          bool autoHide=true,
                          AMTL::ToastInfoPosition showPos = AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                          AMTL::ToastInfoType infoType = AMTL::ToastInfoType::TIP_DEFAULT);

public slots:
    void pairUniConnectionPoint(bool linkStatus,UniConnectionPointPtr target);

    void tickOneTime(bool tickZH){
        if(tickZH){
            //make a zero-high tick
            auto iter = _comSceneIdMap.begin();
            while(iter != _comSceneIdMap.end()){
                iter.key()->tick(TICK_TYPE::HIGH_ZERO);
            }
        }else{
            //make a zero-high tick
            auto iter = _comSceneIdMap.begin();
            while(iter != _comSceneIdMap.end()){
                iter.key()->tick(TICK_TYPE::ZERO_HIGH);
            }
        }
    }
public:
    bool loadGraphicFromXMl(const QString& filePath, QVector<AbstractConInterface*>& comVec);

    bool saveGraphicToXML(const QString& filePath);

    //创建一个toast info
    void makeToastInfo(QString infoTitle,
                       QString info,
                       bool autoHide=true,
                       AMTL::ToastInfoPosition showPos = AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                       AMTL::ToastInfoType infoType = AMTL::ToastInfoType::TIP_DEFAULT);


public:
    AbstractConInterface* addComponent(AbstractConInterface* comItem);
    AbstractConInterface* creatComponent(AbstractConInterface* factory);

protected:
    AbstractConInterface* addComponentImpl(AbstractConInterface* comItem);
    void removeComponentImpl(QObject *objPtr);
    AbstractConInterface* creatComponentImpl(AbstractConInterface* factory);

private:
    bool loadGraphicFromXmlImpl(const QString& filePath, QVector<AbstractConInterface*>& comVec);
    bool loadLinks(QXmlStreamReader& reader);
    bool loadComAllConnectionLinks(QXmlStreamReader& reader,AbstractConInterface* startElement);
    bool loadConnectionPointLine(QXmlStreamReader& reader,AbstractConInterface* startElement,long curCCPId,int lineNum);

    bool saveGraphicToXMLImpl(const QString &filePath);

private:
    UniConnectionPointPtr _firstPair;

    long _curScneId;

    QMap<long,AbstractConInterface*> _sceneIdComMap;
    QMap<AbstractConInterface*, long> _comSceneIdMap;

    //interface
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
MAKE_AUTO_PTR(AmtlGraphicsScene);

//using AmtlGraphicsScenePtr = QWeakPointer<AmtlGraphicsScene>;
//using AmtlGraphicsSceneSPtr = QSharedPointer<AmtlGraphicsScene>;

#endif // AMTLGRAPHICSSCENE_H
