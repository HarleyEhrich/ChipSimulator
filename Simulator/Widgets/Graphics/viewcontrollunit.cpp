#include "viewcontrollunit.h"
#include "ui_viewcontrollunit.h"

#include <QGraphicsEffect>

ViewControllUnit::ViewControllUnit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewControllUnit)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect* effect=new QGraphicsDropShadowEffect();

    effect->setColor(Qt::gray);
    effect->setOffset(0,0);
    effect->setBlurRadius(8);
    this->setGraphicsEffect(effect);
}

ViewControllUnit::~ViewControllUnit()
{
    delete ui;
}


void ViewControllUnit::setCurZoomRatio(qreal newCurZoomRatio)
{
    if(_curZoomRatio==newCurZoomRatio){
        return ;
    }
    _curZoomRatio = newCurZoomRatio;
    ui->scale_ratio_dsp->setValue(_curZoomRatio);
}


void ViewControllUnit::on_lock_view_btn_clicked(bool checked)
{
    if(checked = VIEW_LOCK){
        ui->lock_view_btn->setToolTip(tr("已锁定，不可编辑视图与组件"));
    }else{
        ui->lock_view_btn->setToolTip("");
    }
    emit tellLockStatusChange(checked);
}


void ViewControllUnit::on_model_btn_clicked(bool checked)
{
    if(SELECT_MOVE_MODEL == checked){
         ui->model_btn->setToolTip(tr("移动/选择"));
    }else{
        ui->model_btn->setToolTip(tr("移动"));
    }

    emit tellModelChange(checked);
}


void ViewControllUnit::on_zoom_in_btn_clicked()
{
    qreal newFactor=(_curZoomRatio+_zoomRatioStep)/_curZoomRatio;

    this->setCurZoomRatio(_curZoomRatio+_zoomRatioStep);

    emit tellZoom(newFactor);
}

void ViewControllUnit::on_zoom_out_btn_clicked()
{
    qreal newFactor=(_curZoomRatio-_zoomRatioStep)/_curZoomRatio;

    this->setCurZoomRatio(_curZoomRatio-_zoomRatioStep);

    emit tellZoom(newFactor);
}


void ViewControllUnit::on_scale_ratio_dsp_valueChanged(double arg1)
{
    if(arg1==_curZoomRatio){
        return ;
    }

    //通过更改double spin box 来更改值了
    qreal curFactor=arg1/_curZoomRatio;

    _curZoomRatio=arg1;

    emit tellZoom(curFactor);
}



