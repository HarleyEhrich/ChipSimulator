#ifndef COMPONENTLISTPAGE_H
#define COMPONENTLISTPAGE_H

#include <QLayout>
#include <QSpacerItem>
#include <QWidget>


#include "Widgets/UiItemWidgets/ComponentWidget.h"
#include "ControlObj/PluginLoaderController.h"

namespace Ui {
class ComponentListPage;
}

class ComponentListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentListPage(QWidget *parent = nullptr);
    ~ComponentListPage();

public:
    void updateList();

private:
    void init();

    void resetList();
private:
    Ui::ComponentListPage *ui;
    QGraphicsDropShadowEffect* _shadowEff;
};

#endif // COMPONENTLISTPAGE_H
