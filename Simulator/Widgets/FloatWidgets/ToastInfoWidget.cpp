#include "ToastInfoWidget.h"
#include "ui_ToastInfoWidget.h"

ToastInfoWidget::ToastInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToastInfoWidget)
{
    ui->setupUi(this);

    init();
}

ToastInfoWidget::~ToastInfoWidget()
{
    delete ui;
}

void ToastInfoWidget::popInfo()
{

}

void ToastInfoWidget::init()
{
    _widgetShadowEff = new QGraphicsDropShadowEffect(this);
    _widgetShadowEff->setColor(Qt::gray);
    _widgetShadowEff->setOffset(0,0);
    _widgetShadowEff->setBlurRadius(6);
    setGraphicsEffect(_widgetShadowEff);

    _containerOpacityEff =new QGraphicsOpacityEffect(this);
    _containerOpacityEff->setOpacity(0.82);
    ui->container->setGraphicsEffect(_containerOpacityEff);

    initAni();
}

void ToastInfoWidget::initAni()
{
    switch (_pos) {
    case AMTL::ToastInfoPosition::TIP_RIGHT_TOP:{
        break;
    }
    case AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM:{


        break;
    }
    case AMTL::ToastInfoPosition::TIP_LEFT_TOP:{

        break;
    }
    case AMTL::ToastInfoPosition::TIP_LEFT_BOTTOM:{
        break;
    }
    case AMTL::ToastInfoPosition::TIP_MID_TOP:{
        break;
    }
    case AMTL::ToastInfoPosition::TIP_MID_BOTTOM:{
        break;
    }
    default:
        break;
    }


    popOutAni = new QPropertyAnimation(this,"geometry");
    QRect startGeo = geometry();
    QRect endGemo = geometry();
    startGeo.setX(startGeo.width() - 10);
    popOutAni->setStartValue(startGeo);
    popOutAni->setEndValue(endGemo);
    popOutAni->setDuration(800);
    popOutAni->setEasingCurve(QEasingCurve::BezierSpline);

}


void ToastInfoWidget::on_clase_btn_clicked()
{
    hide();
    deleteLater();
}


void ToastInfoWidget::on_fold_btn_clicked(bool checked)
{
    //true==fold this
    if(checked){
        ui->container->hide();
    }else{
        ui->container->show();
    }
    //false unfold this
}

