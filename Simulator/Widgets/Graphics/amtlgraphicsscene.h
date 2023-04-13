#ifndef AMTLGRAPHICSSCENE_H
#define AMTLGRAPHICSSCENE_H

#include <QDebug>
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

#include "include/project_include.h"


class AmtlGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
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
    explicit AmtlGraphicsScene(QObject *parent = nullptr);


    bool registerUniConnectionPoint(UniConnectionPoint* target);

    //创建一个toast info
    void makeToastInfo(QString infoTitle,
                        QString info,
                        bool autoHide=true,
                        AMTL::ToastInfoPosition showPos = AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                        AMTL::ToastInfoType infoType = AMTL::ToastInfoType::TIP_DEFAULT);

protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private slots:


private:
    QTimer _doubleClickTimer;
    int _clickInterval=100;
    QGraphicsSceneMouseEvent *_clickEvent;

    UniConnectionPointPtr _firstPair;
//    QVector<UniConnectionPointPtr> _pairUniConPointVec;
};

#endif // AMTLGRAPHICSSCENE_H
