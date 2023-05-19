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

//Sig and slots
signals:
    void requestToastInfo(QString infoTitle,
                   QString info,
                   bool autoHide=true,
                   AMTL::ToastInfoPosition showPos = AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                   AMTL::ToastInfoType infoType = AMTL::ToastInfoType::TIP_DEFAULT);

public slots:
    void pairUniConnectionPoint(bool linkStatus,UniConnectionPointPtr target);

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
    void removeComponentImpl(long sceneId,AbstractConInterface* comptr);
    AbstractConInterface* creatComponentImpl(AbstractConInterface* factory);

private:
    UniConnectionPointPtr _firstPair;

    long _curScneId;

    QMap<long,AbstractConInterface*> _sceneIdComMap;
    QMap<AbstractConInterface*, long> _comSceneIdMap;

    //interface
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
MAKE_AUTO_PTR(AmtlGraphicsScene);

//using AmtlGraphicsScenePtr = QWeakPointer<AmtlGraphicsScene>;
//using AmtlGraphicsSceneSPtr = QSharedPointer<AmtlGraphicsScene>;

#endif // AMTLGRAPHICSSCENE_H
