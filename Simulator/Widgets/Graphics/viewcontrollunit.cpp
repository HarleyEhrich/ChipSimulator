#include "viewcontrollunit.h"
#include "ui_viewcontrollunit.h"

#include <QGraphicsEffect>

ViewControllUnit::ViewControllUnit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewControllUnit)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect* effect=new QGraphicsDropShadowEffect();

    effect->setColor(Qt::black);
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
    this->ui->scale_ratio_dsp->setValue(_curZoomRatio);
}

void ViewControllUnit::on_zoom_in_btn_clicked()
{
    qreal newFactor=(_curZoomRatio+_zoomRatioStep)/_curZoomRatio;

    this->setCurZoomRatio(_curZoomRatio+_zoomRatioStep);

    emit zoom(newFactor);
}




void ViewControllUnit::on_zoom_out_btn_clicked()
{
    qreal newFactor=(_curZoomRatio-_zoomRatioStep)/_curZoomRatio;

    this->setCurZoomRatio(_curZoomRatio-_zoomRatioStep);

    emit zoom(newFactor);
}


void ViewControllUnit::on_scale_ratio_dsp_valueChanged(double arg1)
{
    if(arg1==_curZoomRatio){
        return ;
    }

    //通过更改double spin box 来更改值了
    qreal curFactor=arg1/_curZoomRatio;

    _curZoomRatio=arg1;

    emit zoom(curFactor);
}

