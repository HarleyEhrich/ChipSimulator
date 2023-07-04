/********************************************************************************
** Form generated from reading UI file 'ComponentListPage.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPONENTLISTPAGE_H
#define UI_COMPONENTLISTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComponentListPage
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *box;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *com_list_sca;
    QWidget *com_list_content;

    void setupUi(QWidget *ComponentListPage)
    {
        if (ComponentListPage->objectName().isEmpty())
            ComponentListPage->setObjectName(QString::fromUtf8("ComponentListPage"));
        ComponentListPage->resize(384, 512);
        ComponentListPage->setFocusPolicy(Qt::TabFocus);
        ComponentListPage->setStyleSheet(QString::fromUtf8("#ComponentListPage{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"#box{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 8px;\n"
"}\n"
"\n"
".QScrollArea{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 8px;\n"
"}\n"
"\n"
"#com_list_content{\n"
"	background-color: transparent;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(ComponentListPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        box = new QFrame(ComponentListPage);
        box->setObjectName(QString::fromUtf8("box"));
        box->setFrameShape(QFrame::StyledPanel);
        box->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(box);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        com_list_sca = new QScrollArea(box);
        com_list_sca->setObjectName(QString::fromUtf8("com_list_sca"));
        com_list_sca->setWidgetResizable(true);
        com_list_sca->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        com_list_content = new QWidget();
        com_list_content->setObjectName(QString::fromUtf8("com_list_content"));
        com_list_content->setGeometry(QRect(0, 0, 368, 496));
        com_list_sca->setWidget(com_list_content);

        verticalLayout_2->addWidget(com_list_sca);


        verticalLayout->addWidget(box);


        retranslateUi(ComponentListPage);

        QMetaObject::connectSlotsByName(ComponentListPage);
    } // setupUi

    void retranslateUi(QWidget *ComponentListPage)
    {
        ComponentListPage->setWindowTitle(QCoreApplication::translate("ComponentListPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComponentListPage: public Ui_ComponentListPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPONENTLISTPAGE_H
