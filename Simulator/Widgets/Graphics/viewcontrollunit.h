#ifndef VIEWCONTROLLUNIT_H
#define VIEWCONTROLLUNIT_H

#include <QWidget>

namespace Ui {
class ViewControllUnit;
}

class ViewControllUnit : public QWidget
{
    Q_OBJECT
signals:
    void zoom(qreal factor);

private slots:


    void on_zoom_in_btn_clicked();

    void on_zoom_out_btn_clicked();

    void on_scale_ratio_dsp_valueChanged(double arg1);

public:
    explicit ViewControllUnit(QWidget *parent = nullptr);
    ~ViewControllUnit();

    void setCurZoomRatio(qreal newCurZoomRatio);

private:
    Ui::ViewControllUnit *ui;

    qreal _zoomRatioStep=0.1;

    qreal _curZoomRatio=1.0;
};

#endif // VIEWCONTROLLUNIT_H
