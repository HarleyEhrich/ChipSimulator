#ifndef CONLINKPOINTITEM_H
#define CONLINKPOINTITEM_H

#include "./AbstractConInterface/include/abstractconinterface.h"

#include <QObject>
#include <QWidget>

class ConLinkPointItem : public AbstractConInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AbstractConInterface_iid FILE "Json/LinkPointItem/LinkPointItem.json")
    Q_INTERFACES(AbstractConInterface)

public:
    explicit ConLinkPointItem(QGraphicsItem *parent = nullptr);

    // AbstractConInterface interface
public slots:
    virtual AbstractConInterface *creat(long sceneId) override;
    virtual void run() override;
    virtual bool loadStatusFormText(const QString &text) override;
    virtual bool saveStatusToText(QString &text) override;
    virtual QVector<QWidget *> getSetWidgetsVec() override;
    virtual QWidget *getSettingPannel() override;

private:
    QVector<QPointF> _drawPath;

    QVector<ConLinkPointItem*> _pairedLinkItemVec;

};

#endif // CONLINKPOINTITEM_H
