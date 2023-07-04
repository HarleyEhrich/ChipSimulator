#include "UniGraphicsItemObject.h"


UniGraphicsItemObject::UniGraphicsItemObject(QObject *obj, QGraphicsItem *parentItem)
    :QObject(obj), QGraphicsItem(parentItem){

}

UniGraphicsItemObject::~UniGraphicsItemObject(){

}
