#ifndef TOASTINFOWIDGET_H
#define TOASTINFOWIDGET_H

#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QWidget>


#include "Include/ProjectInclude.h"


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

    QTimer* hideTimer;

    QGraphicsDropShadowEffect* _widgetShadowEff=nullptr;
    QGraphicsOpacityEffect* _containerOpacityEff=nullptr;
    QPropertyAnimation* popOutAni;
    QPropertyAnimation* popInAni;

public:
    static void quickToast(QString infoTitle,
                           QString info,
                           bool autoHide=true,
                           AMTL::ToastInfoPosition showPos = AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                           AMTL::ToastInfoType infoType = AMTL::ToastInfoType::TIP_DEFAULT){

    }

    static void setDeaWidget(QWidget* widget){
        if(widget == nullptr) return ;
        connect(widget,&QWidget::destroyed,[]{
            ToastInfoWidget::resetDeaWidet();
        });

        __deaWidget = widget;
    }

    static void resetDeaWidet(){
        __deaWidget  = nullptr;
    }

private:
    inline static QVector<ToastInfoWidget*> _ltInfoShow;//left top
    inline static QVector<ToastInfoWidget*> _lbInfoShow;//right bottom

    inline static QVector<ToastInfoWidget*> _rtInfoShow;//Right Top
    inline static QVector<ToastInfoWidget*> _rbInfoShow;//Right Bottom

    inline static QVector<ToastInfoWidget*> _mtInfoShow;//mid Top
    inline static QVector<ToastInfoWidget*> _mbInfoShow;//mid Bottom

    inline static QWidget* __deaWidget=nullptr;
};

#endif // TOASTINFOWIDGET_H
