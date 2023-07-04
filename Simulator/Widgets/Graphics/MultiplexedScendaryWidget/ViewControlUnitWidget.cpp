#include "ViewControlUnitWidget.h"
#include "ui_ViewControlUnitWidget.h"






ViewControlUnitWidget::ViewControlUnitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewControlUnitWidget)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect* effect=new QGraphicsDropShadowEffect();

    effect->setColor(Qt::gray);
    effect->setOffset(0,0);
    effect->setBlurRadius(8);
    setGraphicsEffect(effect);
}

ViewControlUnitWidget::~ViewControlUnitWidget()
{
    delete ui;
}

//Private Slots
void ViewControlUnitWidget::on_align_bottom_tbtn_clicked()
{
    emit tellAlignBottom();
}

void ViewControlUnitWidget::on_align_center_tbtn_clicked()
{
    emit tellAlignCenter();
}

void ViewControlUnitWidget::on_align_end_tbtn_clicked()
{
    emit tellAlignEnd();
}

void ViewControlUnitWidget::on_align_middle_tbtn_clicked()
{
    emit tellAlignMiddle();
}

void ViewControlUnitWidget::on_align_start_tbtn_clicked()
{
    emit tellAlignStart();
}

void ViewControlUnitWidget::on_align_top_tbtn_clicked()
{
    emit tellAlignTop();
}

void ViewControlUnitWidget::on_lock_view_tbtn_clicked(bool checked)
{
    if(VIEW_LOCK == checked){
        ui->lock_view_tbtn->setToolTip(tr("已锁定，不可编辑视图与组件"));
    }else{
        ui->lock_view_tbtn->setToolTip("");
    }

    emit tellLockStatusChange(checked);
}

void ViewControlUnitWidget::on_model_tbtn_clicked(bool checked)
{
    if(SELECT_MOVE_MODEL == checked){
        ui->model_tbtn->setToolTip(tr("移动/选择"));
    }else{
        ui->model_tbtn->setToolTip(tr("移动"));
    }

    emit tellModelChange(checked);
}

void ViewControlUnitWidget::on_scale_ratio_dsp_valueChanged(double arg1)
{
    if(arg1==_curZoomRatio){
        return ;
    }

    //通过更改double spin box 来更改值了
    qreal curFactor=arg1/_curZoomRatio;

    _curZoomRatio=arg1;

    emit tellZoom(curFactor);
}

void ViewControlUnitWidget::on_zoom_in_tbtn_clicked()
{
    qreal newFactor=(_curZoomRatio+_zoomRatioStep)/_curZoomRatio;

    this->setCurZoomRatio(_curZoomRatio+_zoomRatioStep);

    emit tellZoom(newFactor);
}

void ViewControlUnitWidget::on_zoom_out_tbtn_clicked()
{
    qreal newFactor=(_curZoomRatio-_zoomRatioStep)/_curZoomRatio;

    this->setCurZoomRatio(_curZoomRatio-_zoomRatioStep);

    emit tellZoom(newFactor);
}

void ViewControlUnitWidget::setCurZoomRatio(qreal newCurZoomRatio)
{
    if(_curZoomRatio==newCurZoomRatio){
        return ;
    }
    _curZoomRatio = newCurZoomRatio;
    ui->scale_ratio_dsp->setValue(_curZoomRatio);
}

qreal ViewControlUnitWidget::setZoomRatio(qreal newZoomRatio)
{
    if(_curZoomRatio==newZoomRatio){
        return newZoomRatio;
    }

    newZoomRatio = scaleZoomRatio(newZoomRatio);//截断放大比例

    _curZoomRatio = newZoomRatio;
    ui->scale_ratio_dsp->setValue(_curZoomRatio);

    return newZoomRatio;
}

void ViewControlUnitWidget::init()
{

}

qreal ViewControlUnitWidget::scaleZoomRatio(const qreal& zoomRatio)
{
    if(zoomRatio > __maxZoomRatio){
        return __maxZoomRatio;
    }

    if(zoomRatio < __minZoomRatio){
        return __minZoomRatio;
    }

    return zoomRatio;
}

