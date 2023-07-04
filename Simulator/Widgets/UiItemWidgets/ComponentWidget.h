#ifndef COMPONENTWIDGET_H
#define COMPONENTWIDGET_H

/**
*    @file:    ComponentWidget.h
*    @brief:   组件选择页面item的ui设定
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-05-18  14:49
*/

#include <QWidget>
#include <abstractconinterface.h>

#include "ControlObj/ElecPageController.h"

namespace Ui {
class ComponentWidget;
}

struct ComponentFullInfoStruct{
    ComponentBasicInfoStruct basicInfo;
    QString category;
    QStringList tags;
};

class ComponentUiItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentUiItemWidget(QWidget *parent = nullptr);
    explicit ComponentUiItemWidget(ComponentFullInfoStruct info, QWidget *parent = nullptr);
    ~ComponentUiItemWidget();

public:
    void setComPtr(AbstractConInterface* com);//del
    void setComInfo(const ComponentFullInfoStruct &newComInfo);

private:
    void init();
    void initComInfoImpl();

private:
    Ui::ComponentWidget *ui;
    QGraphicsDropShadowEffect* _shadowEff;

    AbstractConInterface* _targetCom=nullptr;
    ComponentFullInfoStruct _comInfo;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};

MAKE_AUTO_PTR(ComponentUiItemWidget);


#endif // COMPONENTWIDGET_H
