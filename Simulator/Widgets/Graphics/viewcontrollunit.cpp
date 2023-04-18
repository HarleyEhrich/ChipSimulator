#include "viewcontrollunit.h"
#include "ui_viewcontrollunit.h"

#include <QGraphicsEffect>
#include <QPainter>

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

//    ui->lock_view_btn->installEventFilter(this);

}

ViewControllUnit::~ViewControllUnit()
{
    delete ui;
}

//Private Slots
void ViewControllUnit::on_align_bottom_tbtn_clicked()
{
    emit tellAlignBottom();
}

void ViewControllUnit::on_align_center_tbtn_clicked()
{
    emit tellAlignCenter();
}

void ViewControllUnit::on_align_end_tbtn_clicked()
{
    emit tellAlignEnd();
}

void ViewControllUnit::on_align_middle_tbtn_clicked()
{
    emit tellAlignMiddle();
}

void ViewControllUnit::on_align_start_tbtn_clicked()
{
    emit tellAlignStart();
}

void ViewControllUnit::on_align_top_tbtn_clicked()
{
    emit tellAlignTop();
}

void ViewControllUnit::on_lock_view_btn_clicked(bool checked)
{
    if(VIEW_LOCK == checked){
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

void ViewControllUnit::setCurZoomRatio(qreal newCurZoomRatio)
{
    if(_curZoomRatio==newCurZoomRatio){
        return ;
    }
    _curZoomRatio = newCurZoomRatio;
    ui->scale_ratio_dsp->setValue(_curZoomRatio);
}

qreal ViewControllUnit::setZoomRatio(qreal newZoomRatio)
{
    if(_curZoomRatio==newZoomRatio){
        return newZoomRatio;
    }

    newZoomRatio = scaleZoomRatio(newZoomRatio);//截断放大比例

    _curZoomRatio = newZoomRatio;
    ui->scale_ratio_dsp->setValue(_curZoomRatio);

    return newZoomRatio;
}

void ViewControllUnit::init()
{

}

qreal ViewControllUnit::scaleZoomRatio(const qreal& zoomRatio)
{
    if(zoomRatio > __maxZoomRatio){
        return __maxZoomRatio;
    }

    if(zoomRatio < __minZoomRatio){
        return __minZoomRatio;
    }

    return zoomRatio;
}



bool ViewControllUnit::eventFilter(QObject *watched, QEvent *event)
{
//    if(event->type() == QEvent::Type::Paint && watched == ui->lock_view_btn){
//        QPainter painter(static_cast<QWidget *>(watched));
//        painter.setRenderHint(QPainter::Antialiasing);
//        painter.drawRect(0,0,10,10);
//        ui->lock_view_btn->pa
//    }

    return false;
}
