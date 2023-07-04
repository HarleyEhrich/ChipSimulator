#include "ComponentListPage.h"
#include "ui_ComponentListPage.h"

ComponentListPage::ComponentListPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentListPage)
{
    ui->setupUi(this);
}

ComponentListPage::~ComponentListPage()
{
    delete ui;
}

void ComponentListPage::updateList(){
    resetList();
}

void ComponentListPage::init(){
    connect(PluginLoaderController::instance(),&PluginLoaderController::pluginLoadDone,this,&ComponentListPage::resetList);

    if(PluginLoaderController::instance()->getComponentAllItemWidgets().size()){
        resetList();
    }
    MAKE_DEA_SHADOW_EFF(_shadowEff,ui->box);

}

void ComponentListPage::resetList(){
    QLayout* contentLay = ui->com_list_content->layout();
    QLayoutItem* spacer;

    if(nullptr == contentLay){
        contentLay = new QVBoxLayout();
        ui->com_list_content->setLayout(contentLay);
        contentLay->setContentsMargins(0,0,0,0);

        spacer = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Expanding);

    }else{
        spacer = contentLay->takeAt(contentLay->count()-1);
        contentLay->removeItem(spacer);
    }

    if(contentLay->count()){
        QWidget* item;//Remove all exixts item
        while (contentLay->count()) {
            item = contentLay->takeAt(0)->widget();
            contentLay->removeWidget(item);
        }
    }

    PluginLoaderController* loader= PluginLoaderController::instance();
    QVector<ComponentUiItemWidgetSPtr> uiWidgets = loader->getComponentAllItemWidgets();

    for(auto& widgetItem : uiWidgets){
        contentLay->addWidget(widgetItem.data());
    }

    contentLay->addItem(spacer);
}
