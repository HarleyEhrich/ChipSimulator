/********************************************************************************
** Form generated from reading UI file 'ComponentWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPONENTWIDGET_H
#define UI_COMPONENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComponentWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QFrame *box;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *main_lay;
    QLabel *com_img;
    QVBoxLayout *com_info_add_lay;
    QLabel *com_name;
    QTextBrowser *com_other_info;

    void setupUi(QWidget *ComponentWidget)
    {
        if (ComponentWidget->objectName().isEmpty())
            ComponentWidget->setObjectName(QString::fromUtf8("ComponentWidget"));
        ComponentWidget->resize(502, 94);
        ComponentWidget->setMinimumSize(QSize(0, 94));
        ComponentWidget->setMaximumSize(QSize(16777215, 109));
        ComponentWidget->setStyleSheet(QString::fromUtf8("#box{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 8px;\n"
"}\n"
"\n"
".QLabel{\n"
"	border: 0px;\n"
"	font: 11pt \"\346\200\235\346\272\220\351\273\221\344\275\223 CN\";\n"
"	padding-left: 4px;\n"
"}\n"
"\n"
".QTextBroswer{\n"
"	background-color: rgb(0, 170, 255);\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(ComponentWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        box = new QFrame(ComponentWidget);
        box->setObjectName(QString::fromUtf8("box"));
        box->setFrameShape(QFrame::StyledPanel);
        box->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(box);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 4, 0, 4);
        main_lay = new QHBoxLayout();
        main_lay->setSpacing(4);
        main_lay->setObjectName(QString::fromUtf8("main_lay"));
        main_lay->setContentsMargins(4, -1, 4, -1);
        com_img = new QLabel(box);
        com_img->setObjectName(QString::fromUtf8("com_img"));
        com_img->setMinimumSize(QSize(52, 52));
        com_img->setMaximumSize(QSize(52, 52));
        com_img->setAlignment(Qt::AlignCenter);

        main_lay->addWidget(com_img);

        com_info_add_lay = new QVBoxLayout();
        com_info_add_lay->setSpacing(4);
        com_info_add_lay->setObjectName(QString::fromUtf8("com_info_add_lay"));
        com_name = new QLabel(box);
        com_name->setObjectName(QString::fromUtf8("com_name"));
        com_name->setMinimumSize(QSize(0, 16));
        com_name->setMaximumSize(QSize(16777215, 16));

        com_info_add_lay->addWidget(com_name);

        com_other_info = new QTextBrowser(box);
        com_other_info->setObjectName(QString::fromUtf8("com_other_info"));
        com_other_info->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        com_other_info->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        com_info_add_lay->addWidget(com_other_info);


        main_lay->addLayout(com_info_add_lay);


        verticalLayout_2->addLayout(main_lay);


        verticalLayout_3->addWidget(box);


        retranslateUi(ComponentWidget);

        QMetaObject::connectSlotsByName(ComponentWidget);
    } // setupUi

    void retranslateUi(QWidget *ComponentWidget)
    {
        ComponentWidget->setWindowTitle(QCoreApplication::translate("ComponentWidget", "Form", nullptr));
        com_img->setText(QString());
        com_name->setText(QCoreApplication::translate("ComponentWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComponentWidget: public Ui_ComponentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPONENTWIDGET_H
