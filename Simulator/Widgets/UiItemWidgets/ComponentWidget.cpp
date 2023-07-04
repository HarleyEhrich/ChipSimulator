#include "ComponentWidget.h"
#include "ui_ComponentWidget.h"

#include "Widgets/FloatWidgets/ToastInfoWidget.h"

ComponentUiItemWidget::ComponentUiItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentWidget)
{
    ui->setupUi(this);
    init();
}

ComponentUiItemWidget::ComponentUiItemWidget(ComponentFullInfoStruct info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentWidget),
    _comInfo(info)
{
    ui->setupUi(this);
    init();
}

ComponentUiItemWidget::~ComponentUiItemWidget()
{
    delete ui;

}

void ComponentUiItemWidget::initComInfoImpl(){
    ui->com_img->setPixmap((*_comInfo.basicInfo.comImage).scaled(50,50,Qt::KeepAspectRatio));
    ui->com_name->setText(_comInfo.basicInfo.comName);

    ui->com_other_info->setText(
        "Author : "+_comInfo.basicInfo.comAuthor +
        "\nDescripty : " + _comInfo.basicInfo.comDesInfo
        );
}

void ComponentUiItemWidget::setComInfo(const ComponentFullInfoStruct &newComInfo)
{
    _comInfo = newComInfo;
    initComInfoImpl();
}

void ComponentUiItemWidget::init(){
    MAKE_DEA_SHADOW_EFF(_shadowEff,this);
    initComInfoImpl();
}

void ComponentUiItemWidget::setComPtr(AbstractConInterface *com){
    if(nullptr == com) return ;
    _targetCom = com;
}



void ComponentUiItemWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if(nullptr != _targetCom){
        auto actPage =  ElecPageController::getCurActPage();
        if(!actPage.isNull()){
            actPage->addANewComponnent(_targetCom);
        }else{
            ToastInfoWidget::quickToast(
                tr("Warning"),
                tr("There's no any electric page active."),
                true,
                AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                AMTL::ToastInfoType::TIP_WARNING);
            qWarning().noquote()DEBUGINFO<<tr("There's no any electric page active.");
        }
    }else{
        assert("This should not be a nullptr.");
    }
}
