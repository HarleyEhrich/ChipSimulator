/********************************************************************************
** Form generated from reading UI file 'ElecPage.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELECPAGE_H
#define UI_ELECPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ElectPage
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *box;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *default_page;
    QVBoxLayout *verticalLayout_3;
    QFrame *dea_page_box;
    QVBoxLayout *verticalLayout_4;
    QWidget *dea_page_container;
    QPushButton *open_project_btn;
    QPushButton *new_project_btn;

    void setupUi(QWidget *ElectPage)
    {
        if (ElectPage->objectName().isEmpty())
            ElectPage->setObjectName(QString::fromUtf8("ElectPage"));
        ElectPage->resize(797, 477);
        verticalLayout = new QVBoxLayout(ElectPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        box = new QFrame(ElectPage);
        box->setObjectName(QString::fromUtf8("box"));
        box->setFrameShape(QFrame::StyledPanel);
        box->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(box);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(box);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        default_page = new QWidget();
        default_page->setObjectName(QString::fromUtf8("default_page"));
        verticalLayout_3 = new QVBoxLayout(default_page);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        dea_page_box = new QFrame(default_page);
        dea_page_box->setObjectName(QString::fromUtf8("dea_page_box"));
        dea_page_box->setFrameShape(QFrame::StyledPanel);
        dea_page_box->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(dea_page_box);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        dea_page_container = new QWidget(dea_page_box);
        dea_page_container->setObjectName(QString::fromUtf8("dea_page_container"));
        open_project_btn = new QPushButton(dea_page_container);
        open_project_btn->setObjectName(QString::fromUtf8("open_project_btn"));
        open_project_btn->setGeometry(QRect(50, 80, 121, 31));
        new_project_btn = new QPushButton(dea_page_container);
        new_project_btn->setObjectName(QString::fromUtf8("new_project_btn"));
        new_project_btn->setGeometry(QRect(50, 30, 111, 31));

        verticalLayout_4->addWidget(dea_page_container);


        verticalLayout_3->addWidget(dea_page_box);

        stackedWidget->addWidget(default_page);

        verticalLayout_2->addWidget(stackedWidget);


        verticalLayout->addWidget(box);


        retranslateUi(ElectPage);

        QMetaObject::connectSlotsByName(ElectPage);
    } // setupUi

    void retranslateUi(QWidget *ElectPage)
    {
        ElectPage->setWindowTitle(QCoreApplication::translate("ElectPage", "Form", nullptr));
        open_project_btn->setText(QCoreApplication::translate("ElectPage", "\346\211\223\345\274\200\347\216\260\346\234\211\345\267\245\347\250\213", nullptr));
        new_project_btn->setText(QCoreApplication::translate("ElectPage", "\346\226\260\345\273\272\345\267\245\347\250\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ElectPage: public Ui_ElectPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELECPAGE_H
