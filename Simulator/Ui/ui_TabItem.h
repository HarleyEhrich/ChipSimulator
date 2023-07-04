/********************************************************************************
** Form generated from reading UI file 'TabItem.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABITEM_H
#define UI_TABITEM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabItem
{
public:
    QHBoxLayout *tab_matser_lay;
    QFrame *box;
    QVBoxLayout *tab_box_lay;
    QWidget *container;
    QHBoxLayout *tab_container_lay;
    QLabel *title;
    QToolButton *close_tbtn;

    void setupUi(QWidget *TabItem)
    {
        if (TabItem->objectName().isEmpty())
            TabItem->setObjectName(QString::fromUtf8("TabItem"));
        TabItem->resize(109, 33);
        TabItem->setStyleSheet(QString::fromUtf8("#box{\n"
"	background-color: #f3f3f3;\n"
"	border: 0px;\n"
"	border-radius:4px;\n"
"	margin: 2px;\n"
"	padding: 2px;\n"
"}\n"
"\n"
"#box:hover{\n"
"	background-color: rgba(0, 43, 91, 180);\n"
"	color: rgb(238, 238, 238);\n"
"}\n"
"\n"
"\n"
"#container .QToolButton{\n"
"	background-color: transparent;\n"
"	border: 1px transparent;\n"
"	border-radius: 2px;\n"
"	padding: 2px 2px 2px 2px;\n"
"}\n"
"\n"
"#container .QToolButton:hover{\n"
"	background-color: rgba(231, 231, 231,220);\n"
"}\n"
"\n"
"#title{\n"
"	font: 400 10pt \"\346\200\235\346\272\220\351\273\221\344\275\223 CN Normal\";\n"
"	min-width: 48px;\n"
"}"));
        tab_matser_lay = new QHBoxLayout(TabItem);
        tab_matser_lay->setSpacing(0);
        tab_matser_lay->setObjectName(QString::fromUtf8("tab_matser_lay"));
        tab_matser_lay->setContentsMargins(0, 0, 0, 0);
        box = new QFrame(TabItem);
        box->setObjectName(QString::fromUtf8("box"));
        box->setFrameShape(QFrame::StyledPanel);
        box->setFrameShadow(QFrame::Raised);
        tab_box_lay = new QVBoxLayout(box);
        tab_box_lay->setSpacing(0);
        tab_box_lay->setObjectName(QString::fromUtf8("tab_box_lay"));
        tab_box_lay->setContentsMargins(0, 0, 0, 0);
        container = new QWidget(box);
        container->setObjectName(QString::fromUtf8("container"));
        tab_container_lay = new QHBoxLayout(container);
        tab_container_lay->setSpacing(4);
        tab_container_lay->setObjectName(QString::fromUtf8("tab_container_lay"));
        tab_container_lay->setContentsMargins(8, 0, 8, 0);
        title = new QLabel(container);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMaximumSize(QSize(16777215, 28));
        title->setLineWidth(0);
        title->setAlignment(Qt::AlignCenter);

        tab_container_lay->addWidget(title);

        close_tbtn = new QToolButton(container);
        close_tbtn->setObjectName(QString::fromUtf8("close_tbtn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tab_widget/TabWidget/close_grey.svg"), QSize(), QIcon::Normal, QIcon::Off);
        close_tbtn->setIcon(icon);
        close_tbtn->setIconSize(QSize(18, 18));

        tab_container_lay->addWidget(close_tbtn);


        tab_box_lay->addWidget(container);


        tab_matser_lay->addWidget(box);


        retranslateUi(TabItem);

        QMetaObject::connectSlotsByName(TabItem);
    } // setupUi

    void retranslateUi(QWidget *TabItem)
    {
        TabItem->setWindowTitle(QCoreApplication::translate("TabItem", "Form", nullptr));
        title->setText(QString());
#if QT_CONFIG(tooltip)
        close_tbtn->setToolTip(QCoreApplication::translate("TabItem", "\345\205\263\351\227\255\350\257\245\351\241\265\351\235\242", nullptr));
#endif // QT_CONFIG(tooltip)
        close_tbtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TabItem: public Ui_TabItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABITEM_H
