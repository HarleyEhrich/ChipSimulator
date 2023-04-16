#ifndef VIEWCONTROLLUNIT_H
#define VIEWCONTROLLUNIT_H

#include <QWidget>

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
    void tellLockStatusChange(bool locked);

    void tellModelChange(bool model);

    void tellZoom(qreal factor);

private slots:
    void on_lock_view_btn_clicked(bool checked);

    void on_model_btn_clicked(bool checked);

    void on_zoom_in_btn_clicked();

    void on_zoom_out_btn_clicked();

    void on_scale_ratio_dsp_valueChanged(double arg1);


public:
    void setCurZoomRatio(qreal newCurZoomRatio);

private:


private:
    Ui::ViewControllUnit *ui;

    qreal _zoomRatioStep=0.1;

    qreal _curZoomRatio=1.0;
};

#endif // VIEWCONTROLLUNIT_H
