#ifndef UNIGRAPHICSITEMOBJECT_H
#define UNIGRAPHICSITEMOBJECT_H


#include <QGraphicsItem>
#include <QObject>

#include "GlobalInclude.h"


class BASICSDK_EXPORT UniGraphicsItemObject : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_INTERFACES(QGraphicsItem)

public:
    UniGraphicsItemObject(QObject* obj=nullptr,QGraphicsItem* parentItem=nullptr);
    virtual ~UniGraphicsItemObject();

public:
    virtual QPointF getRealItemCenterScenePos() = 0;
    virtual QRectF getRealBoudingRect() = 0;
};

MAKE_AUTO_PTR(UniGraphicsItemObject)

#endif // UNIGRAPHICSITEMOBJECT_H
