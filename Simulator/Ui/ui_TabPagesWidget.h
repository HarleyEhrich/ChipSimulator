/********************************************************************************
** Form generated from reading UI file 'TabPagesWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABPAGESWIDGET_H
#define UI_TABPAGESWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Widgets/PageWidget/CustomTabBar.h"

QT_BEGIN_NAMESPACE

class Ui_TabPagesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *tab_item_box;
    QHBoxLayout *tab_lay;
    CustomTabBar *tabbar_widget;
    QHBoxLayout *tab_item_ley;
    QSpacerItem *tabbar_spacer;
    QPushButton *add_dea_page_btn;
    QStackedWidget *Content;

    void setupUi(QWidget *TabPagesWidget)
    {
        if (TabPagesWidget->objectName().isEmpty())
            TabPagesWidget->setObjectName(QString::fromUtf8("TabPagesWidget"));
        TabPagesWidget->resize(597, 201);
        TabPagesWidget->setStyleSheet(QString::fromUtf8("#FlatTabWidget{\n"
"	border: 0px;\n"
"}\n"
"\n"
"#Content{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"#tab_item_box{\n"
"	background-color: rgb(250, 250, 250);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 6px;\n"
"	margin: 0px;\n"
"}\n"
"\n"
"#add_dea_page_btn{\n"
"    background-color: transparent;\n"
"	border: 0px;\n"
"	padding: 4px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(TabPagesWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tab_item_box = new QFrame(TabPagesWidget);
        tab_item_box->setObjectName(QString::fromUtf8("tab_item_box"));
        tab_item_box->setMinimumSize(QSize(0, 48));
        tab_item_box->setMaximumSize(QSize(16777215, 48));
        tab_lay = new QHBoxLayout(tab_item_box);
        tab_lay->setSpacing(0);
        tab_lay->setObjectName(QString::fromUtf8("tab_lay"));
        tab_lay->setContentsMargins(0, 0, 0, 0);
        tabbar_widget = new CustomTabBar(tab_item_box);
        tabbar_widget->setObjectName(QString::fromUtf8("tabbar_widget"));
        tabbar_widget->setMinimumSize(QSize(0, 42));
        tabbar_widget->setMaximumSize(QSize(16777215, 42));
        tabbar_widget->setStyleSheet(QString::fromUtf8(""));
        tab_item_ley = new QHBoxLayout(tabbar_widget);
        tab_item_ley->setSpacing(0);
        tab_item_ley->setObjectName(QString::fromUtf8("tab_item_ley"));
        tab_item_ley->setContentsMargins(0, 0, 0, 0);
        tabbar_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        tab_item_ley->addItem(tabbar_spacer);


        tab_lay->addWidget(tabbar_widget);

        add_dea_page_btn = new QPushButton(tab_item_box);
        add_dea_page_btn->setObjectName(QString::fromUtf8("add_dea_page_btn"));
        add_dea_page_btn->setMinimumSize(QSize(32, 32));
        add_dea_page_btn->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tab_widget/TabWidget/add_ori.svg"), QSize(), QIcon::Normal, QIcon::Off);
        add_dea_page_btn->setIcon(icon);

        tab_lay->addWidget(add_dea_page_btn);


        verticalLayout->addWidget(tab_item_box);

        Content = new QStackedWidget(TabPagesWidget);
        Content->setObjectName(QString::fromUtf8("Content"));
        Content->setStyleSheet(QString::fromUtf8(""));
        Content->setLineWidth(0);

        verticalLayout->addWidget(Content);


        retranslateUi(TabPagesWidget);

        Content->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(TabPagesWidget);
    } // setupUi

    void retranslateUi(QWidget *TabPagesWidget)
    {
        TabPagesWidget->setWindowTitle(QCoreApplication::translate("TabPagesWidget", "FlatTabWidget", nullptr));
        add_dea_page_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TabPagesWidget: public Ui_TabPagesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABPAGESWIDGET_H
