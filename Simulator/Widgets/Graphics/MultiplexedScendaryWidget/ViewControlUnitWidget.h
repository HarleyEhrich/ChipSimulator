#ifndef VIEWCONTROLUNITWIDGET_H
#define VIEWCONTROLUNITWIDGET_H

#include <QGraphicsEffect>
#include <QPainter>
#include <QWidget>
#include <QPluginLoader>
#include <QMetaObject>

#include "Include/ProjectInclude.h"

#include <abstractconinterface.h>

namespace Ui {
    class ViewControlUnitWidget;
}


#define VIEW_LOCK true
#define VIEW_UNLOCK false

#define MOVE_MODEL false
#define SELECT_MOVE_MODEL true

class ViewControlUnitWidget : public QWidget
{
    Q_OBJECT
public:


public:
    explicit ViewControlUnitWidget(QWidget *parent = nullptr);
    virtual ~ViewControlUnitWidget();

signals:
    //水平对齐底部
    void tellAlignBottom();
    //垂直对齐中间
    void tellAlignCenter();
    //垂直对齐右侧
    void tellAlignEnd();
    //水平对齐中间
    void tellAlignMiddle();
    //垂直对齐左侧
    void tellAlignStart();
    //水平对齐顶部
    void tellAlignTop();
    void tellLockStatusChange(bool locked);
    void tellModelChange(bool model);
    void tellZoom(qreal factor);

private slots:
    void on_align_bottom_tbtn_clicked();
    void on_align_center_tbtn_clicked();
    void on_align_end_tbtn_clicked();
    void on_align_middle_tbtn_clicked();
    void on_align_start_tbtn_clicked();
    void on_align_top_tbtn_clicked();
    void on_lock_view_tbtn_clicked(bool checked);
    void on_model_tbtn_clicked(bool checked);
    void on_scale_ratio_dsp_valueChanged(double arg1);
    void on_zoom_in_tbtn_clicked();
    void on_zoom_out_tbtn_clicked();

public:
    void setCurZoomRatio(qreal newCurZoomRatio);//del

    qreal setZoomRatio(qreal newZoomRatio);

private:
    void init();



private:
    Ui::ViewControlUnitWidget *ui;

    qreal _zoomRatioStep=0.1;

    qreal _curZoomRatio=1.0;



public:
    static inline qreal scaleZoomRatio(const qreal& zoomRatio);
private:
    inline static qreal __maxZoomRatio=8.0f;
    inline static qreal __minZoomRatio = 0.3f;


};

#endif // VIEWCONTROLUNITWIDGET_H
