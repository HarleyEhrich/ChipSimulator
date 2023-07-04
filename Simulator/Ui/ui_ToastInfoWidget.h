/********************************************************************************
** Form generated from reading UI file 'ToastInfoWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOASTINFOWIDGET_H
#define UI_TOASTINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToastInfoWidget
{
public:
    QHBoxLayout *to_widget_layout;
    QFrame *container;
    QVBoxLayout *to_container_layout;
    QHBoxLayout *title_btn_lay;
    QLabel *info_icon;
    QLabel *info_title;
    QSpacerItem *horizontalSpacer;
    QToolButton *fold_btn;
    QToolButton *clase_btn;
    QHBoxLayout *info_icon_lay;
    QTextBrowser *info_tb;

    void setupUi(QWidget *ToastInfoWidget)
    {
        if (ToastInfoWidget->objectName().isEmpty())
            ToastInfoWidget->setObjectName(QString::fromUtf8("ToastInfoWidget"));
        ToastInfoWidget->resize(320, 82);
        ToastInfoWidget->setStyleSheet(QString::fromUtf8("#ToastInfoWidget{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"#container{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 6px;\n"
"}\n"
"\n"
"#container QToolButton{\n"
"	background-color: transparent;\n"
"	border: 0px;\n"
"	border-radius: 2px;\n"
"	margin: 0px 0px,0px,0px;\n"
"	padding: 4px, 4px,4px,4px;\n"
"}\n"
"\n"
"#container QToolButton::hover{\n"
"	background-color: rgb(221, 221, 221);\n"
"	border: 1px solid transparent;\n"
"}\n"
"\n"
"#info_tb{\n"
"	background-color: transparent;\n"
"	border: 0px;\n"
"	border-radius: 6px;\n"
"	margin: 2px 2px,2px,2px;\n"
"	padding: 3px, 3px,3px,3px;\n"
"	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"#info_tb::hover{\n"
"	background-color: rgba(240, 240, 240, 220);\n"
"}\n"
"\n"
""));
        to_widget_layout = new QHBoxLayout(ToastInfoWidget);
        to_widget_layout->setSpacing(0);
        to_widget_layout->setObjectName(QString::fromUtf8("to_widget_layout"));
        to_widget_layout->setContentsMargins(0, 0, 0, 0);
        container = new QFrame(ToastInfoWidget);
        container->setObjectName(QString::fromUtf8("container"));
        container->setFrameShape(QFrame::StyledPanel);
        container->setFrameShadow(QFrame::Raised);
        to_container_layout = new QVBoxLayout(container);
        to_container_layout->setSpacing(0);
        to_container_layout->setObjectName(QString::fromUtf8("to_container_layout"));
        to_container_layout->setContentsMargins(8, 2, 8, 2);
        title_btn_lay = new QHBoxLayout();
        title_btn_lay->setSpacing(4);
        title_btn_lay->setObjectName(QString::fromUtf8("title_btn_lay"));
        info_icon = new QLabel(container);
        info_icon->setObjectName(QString::fromUtf8("info_icon"));
        info_icon->setMinimumSize(QSize(16, 16));
        info_icon->setMaximumSize(QSize(16, 16));
        info_icon->setPixmap(QPixmap(QString::fromUtf8(":/toast_info/toastinfoicon/defalut.png")));
        info_icon->setScaledContents(true);
        info_icon->setAlignment(Qt::AlignCenter);

        title_btn_lay->addWidget(info_icon);

        info_title = new QLabel(container);
        info_title->setObjectName(QString::fromUtf8("info_title"));

        title_btn_lay->addWidget(info_title);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        title_btn_lay->addItem(horizontalSpacer);

        fold_btn = new QToolButton(container);
        fold_btn->setObjectName(QString::fromUtf8("fold_btn"));
        fold_btn->setMinimumSize(QSize(18, 18));
        fold_btn->setMaximumSize(QSize(18, 18));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/toast_info/toastinfoicon/fold_info.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/toast_info/toastinfoicon/expand_info.png"), QSize(), QIcon::Normal, QIcon::On);
        fold_btn->setIcon(icon);
        fold_btn->setIconSize(QSize(16, 16));
        fold_btn->setCheckable(true);

        title_btn_lay->addWidget(fold_btn);

        clase_btn = new QToolButton(container);
        clase_btn->setObjectName(QString::fromUtf8("clase_btn"));
        clase_btn->setMinimumSize(QSize(18, 18));
        clase_btn->setMaximumSize(QSize(18, 18));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/toast_info/toastinfoicon/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        clase_btn->setIcon(icon1);
        clase_btn->setIconSize(QSize(16, 16));

        title_btn_lay->addWidget(clase_btn);


        to_container_layout->addLayout(title_btn_lay);

        info_icon_lay = new QHBoxLayout();
        info_icon_lay->setSpacing(4);
        info_icon_lay->setObjectName(QString::fromUtf8("info_icon_lay"));
        info_tb = new QTextBrowser(container);
        info_tb->setObjectName(QString::fromUtf8("info_tb"));
        info_tb->setMaximumSize(QSize(16777215, 48));
        info_tb->setLineWidth(0);

        info_icon_lay->addWidget(info_tb);


        to_container_layout->addLayout(info_icon_lay);


        to_widget_layout->addWidget(container);


        retranslateUi(ToastInfoWidget);

        QMetaObject::connectSlotsByName(ToastInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *ToastInfoWidget)
    {
        ToastInfoWidget->setWindowTitle(QCoreApplication::translate("ToastInfoWidget", "Form", nullptr));
        info_icon->setText(QString());
        info_title->setText(QCoreApplication::translate("ToastInfoWidget", "Title", nullptr));
        fold_btn->setText(QString());
        clase_btn->setText(QString());
        info_tb->setHtml(QCoreApplication::translate("ToastInfoWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\210\221\346\230\257\344\270\200\346\235\241\346\265\213\350\257\225\344\275\277\347\224\250\347\232\204\344\277\241\346\201\257\357\274\214\350\257\267\346\263\250\346\204\217\346\210\221\347\232\204\345\206\205\345\256\271\357\274\214\345\271\266\344\273\224\347\273\206\351\230\205\350\257\273\345\220\247!</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToastInfoWidget: public Ui_ToastInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOASTINFOWIDGET_H
