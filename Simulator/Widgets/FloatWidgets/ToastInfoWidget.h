#ifndef TOASTINFOWIDGET_H
#define TOASTINFOWIDGET_H

#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPropertyAnimation >
#include <QWidget>


#include "include/project_include.h"


namespace Ui {
class ToastInfoWidget;
}

class ToastInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToastInfoWidget(QWidget *parent = nullptr);
    virtual ~ToastInfoWidget();

    void popInfo();

private slots:
    void on_clase_btn_clicked();

    void on_fold_btn_clicked(bool checked);

private:
    void init();
    void initAni();
private:
    Ui::ToastInfoWidget *ui;

    AMTL::ToastInfoPosition _pos;

    QGraphicsDropShadowEffect* _widgetShadowEff=nullptr;
    QGraphicsOpacityEffect* _containerOpacityEff=nullptr;
    QPropertyAnimation* popOutAni;
    QPropertyAnimation* popInAni;



//    QRect widgetLayExpandGeo;
//    QRect widgetLayFoldGeo;
//    QRect infoLayExpandGeo;
//    QRect infoTbLayFoldGeo;
//    QAnimationGroup expandAniGroup;
//    QAnimationGroup foldAniGroup;

};

#endif // TOASTINFOWIDGET_H
