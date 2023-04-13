#include "conlinkpointitem.h"

ConLinkPointItem::ConLinkPointItem(QGraphicsItem *parent) : AbstractConInterface(parent)
{

}


AbstractConInterface *ConLinkPointItem::creat(long sceneId)
{
    auto newInstance=new ConLinkPointItem(nullptr);
    newInstance->setSceneId(sceneId);
    return newInstance;
}

void ConLinkPointItem::run()
{

}

bool ConLinkPointItem::loadStatusFormText(const QString &text)
{
    return false;
}

bool ConLinkPointItem::saveStatusToText(QString &text)
{
    return false;
}

QVector<QWidget *> ConLinkPointItem::getSetWidgetsVec()
{
    return QVector<QWidget*>();
}

QWidget *ConLinkPointItem::getSettingPannel()
{
    return nullptr;
}


