#ifndef VIEWCONTROLLUNIT_H
#define VIEWCONTROLLUNIT_H

#include <QWidget>

#include "Include/project_include.h"

namespace Ui {
    class ViewControllUnit;
}


#define VIEW_LOCK true
#define VIEW_UNLOCK false

#define MOVE_MODEL false
#define SELECT_MOVE_MODEL true

class ViewControllUnit : public QWidget
{
    Q_OBJECT
public:


public:
    explicit ViewControllUnit(QWidget *parent = nullptr);
    virtual ~ViewControllUnit();

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
    void on_lock_view_btn_clicked(bool checked);
    void on_model_btn_clicked(bool checked);
    void on_scale_ratio_dsp_valueChanged(double arg1);
    void on_zoom_in_btn_clicked();
    void on_zoom_out_btn_clicked();

public:
    void setCurZoomRatio(qreal newCurZoomRatio);//del

    qreal setZoomRatio(qreal newZoomRatio);

private:
    void init();



private:
    Ui::ViewControllUnit *ui;

    qreal _zoomRatioStep=0.1;

    qreal _curZoomRatio=1.0;

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

public:
    static inline qreal scaleZoomRatio(const qreal& zoomRatio);
private:
    inline static qreal __maxZoomRatio=8.0f;
    inline static qreal __minZoomRatio = 0.3f;


};

#endif // VIEWCONTROLLUNIT_H
