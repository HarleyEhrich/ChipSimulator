/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Widgets/PageWidget/TabPagesWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actiontxt;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_7;
    QFrame *sidebar_box;
    QHBoxLayout *horizontalLayout;
    QWidget *sidebar_container;
    QVBoxLayout *verticalLayout_9;
    QToolButton *open_name_tbtn;
    QToolButton *home_tbtn;
    QToolButton *open_page_tbtn;
    QToolButton *open_file_tbtn;
    QToolButton *component_tbtn;
    QToolButton *component_tbtn_2;
    QSpacerItem *sidebar_spacer;
    QToolButton *settings_tbtn;
    QFrame *main_page_box;
    QVBoxLayout *verticalLayout_4;
    QWidget *main_page_container;
    QVBoxLayout *verticalLayout_5;
    QSplitter *page_info_spliter;
    QFrame *page_tab_box;
    QVBoxLayout *verticalLayout;
    QWidget *page_tab_container;
    QVBoxLayout *verticalLayout_3;
    TabPagesWidget *page_tab_widget;
    QFrame *info_tab_box;
    QHBoxLayout *horizontalLayout_8;
    QWidget *info_tab_container;
    QHBoxLayout *horizontalLayout_3;
    TabPagesWidget *info_tab_widget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1007, 662);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color: #f3f3f3;\n"
"	border: 0px;\n"
"}\n"
"\n"
"\n"
"\n"
"/*---Menu bar---*/\n"
"#menubar{\n"
"	background-color: #002b5b;\n"
"	color: #fefefe;\n"
"\n"
"	padding: 4px;\n"
"	\n"
"	font: 500 10pt \"\346\200\235\346\272\220\351\273\221\344\275\223 CN Medium\";\n"
"	padding-left: 48px;\n"
"}\n"
"\n"
"/*menu item at the menubar*/\n"
"QMenuBar::item {\n"
"    background-color: transparent;\n"
"    border-radius: 0px;\n"
"    color: #ffffff;\n"
"    padding-left: 8px;\n"
"    padding-right: 8px;\n"
"    padding-top:2px;\n"
"    padding-bottom: 2px;\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"\n"
"    border-bottom: 2px solid white;\n"
"}\n"
"\n"
""));
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::GroupedDragging|QMainWindow::VerticalTabs);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actiontxt = new QAction(MainWindow);
        actiontxt->setObjectName(QString::fromUtf8("actiontxt"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("#centralwidget{\n"
"	background-color: transparent;\n"
"	border: 0px solid transparent;\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"}"));
        horizontalLayout_7 = new QHBoxLayout(centralwidget);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        sidebar_box = new QFrame(centralwidget);
        sidebar_box->setObjectName(QString::fromUtf8("sidebar_box"));
        sidebar_box->setMaximumSize(QSize(49, 16777215));
        sidebar_box->setStyleSheet(QString::fromUtf8("#sidebar_box{\n"
"	border: 0px solid;\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"}\n"
"\n"
"#sidebar_container{\n"
"	background-color:  rgb(0, 43, 91);\n"
"	border: 0px solid;\n"
"	/*border-radius: 6px;*/\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"}\n"
"\n"
"#sidebar_container .QToolButton{\n"
"	background-color: transparent;\n"
"	color: rgb(255, 255, 255);\n"
"	border: 0px transparent;\n"
"	border-left: 2px solid  transparent;\n"
"	border-right: 2px solid  transparent;\n"
"}\n"
"\n"
"#sidebar_container .QToolButton:hover{\n"
"	border-left: 2px solid rgb(255, 255, 255);\n"
"}\n"
"\n"
"#sidebar_container .QToolButton:checked{\n"
"	border-left: 2px solid rgb(255, 255, 255);\n"
"}"));
        sidebar_box->setFrameShape(QFrame::StyledPanel);
        sidebar_box->setFrameShadow(QFrame::Raised);
        sidebar_box->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(sidebar_box);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebar_container = new QWidget(sidebar_box);
        sidebar_container->setObjectName(QString::fromUtf8("sidebar_container"));
        verticalLayout_9 = new QVBoxLayout(sidebar_container);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        open_name_tbtn = new QToolButton(sidebar_container);
        open_name_tbtn->setObjectName(QString::fromUtf8("open_name_tbtn"));
        open_name_tbtn->setMinimumSize(QSize(48, 48));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainwindow/menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        open_name_tbtn->setIcon(icon);
        open_name_tbtn->setIconSize(QSize(24, 24));
        open_name_tbtn->setCheckable(false);
        open_name_tbtn->setChecked(false);
        open_name_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_9->addWidget(open_name_tbtn);

        home_tbtn = new QToolButton(sidebar_container);
        home_tbtn->setObjectName(QString::fromUtf8("home_tbtn"));
        home_tbtn->setMinimumSize(QSize(48, 48));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/mainwindow/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        home_tbtn->setIcon(icon1);
        home_tbtn->setIconSize(QSize(24, 24));
        home_tbtn->setCheckable(true);
        home_tbtn->setChecked(false);
        home_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_9->addWidget(home_tbtn);

        open_page_tbtn = new QToolButton(sidebar_container);
        open_page_tbtn->setObjectName(QString::fromUtf8("open_page_tbtn"));
        open_page_tbtn->setMinimumSize(QSize(48, 48));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/mainwindow/open_page.png"), QSize(), QIcon::Normal, QIcon::Off);
        open_page_tbtn->setIcon(icon2);
        open_page_tbtn->setIconSize(QSize(24, 24));
        open_page_tbtn->setCheckable(true);
        open_page_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_9->addWidget(open_page_tbtn);

        open_file_tbtn = new QToolButton(sidebar_container);
        open_file_tbtn->setObjectName(QString::fromUtf8("open_file_tbtn"));
        open_file_tbtn->setMinimumSize(QSize(48, 48));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/mainwindow/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        open_file_tbtn->setIcon(icon3);
        open_file_tbtn->setIconSize(QSize(24, 24));
        open_file_tbtn->setCheckable(true);
        open_file_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_9->addWidget(open_file_tbtn);

        component_tbtn = new QToolButton(sidebar_container);
        component_tbtn->setObjectName(QString::fromUtf8("component_tbtn"));
        component_tbtn->setMinimumSize(QSize(48, 48));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/mainwindow/component.png"), QSize(), QIcon::Normal, QIcon::Off);
        component_tbtn->setIcon(icon4);
        component_tbtn->setIconSize(QSize(24, 24));
        component_tbtn->setCheckable(true);
        component_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_9->addWidget(component_tbtn);

        component_tbtn_2 = new QToolButton(sidebar_container);
        component_tbtn_2->setObjectName(QString::fromUtf8("component_tbtn_2"));
        component_tbtn_2->setMinimumSize(QSize(48, 48));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/mainwindow/test.png"), QSize(), QIcon::Normal, QIcon::Off);
        component_tbtn_2->setIcon(icon5);
        component_tbtn_2->setIconSize(QSize(24, 24));
        component_tbtn_2->setCheckable(true);
        component_tbtn_2->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_9->addWidget(component_tbtn_2);

        sidebar_spacer = new QSpacerItem(20, 483, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(sidebar_spacer);

        settings_tbtn = new QToolButton(sidebar_container);
        settings_tbtn->setObjectName(QString::fromUtf8("settings_tbtn"));
        settings_tbtn->setMinimumSize(QSize(48, 48));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/mainwindow/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        settings_tbtn->setIcon(icon6);
        settings_tbtn->setIconSize(QSize(24, 24));
        settings_tbtn->setCheckable(true);
        settings_tbtn->setChecked(false);
        settings_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_9->addWidget(settings_tbtn);


        horizontalLayout->addWidget(sidebar_container);


        horizontalLayout_7->addWidget(sidebar_box);

        main_page_box = new QFrame(centralwidget);
        main_page_box->setObjectName(QString::fromUtf8("main_page_box"));
        main_page_box->setStyleSheet(QString::fromUtf8("#main_page_box{\n"
"	/*\345\217\263\344\276\247\351\241\265\351\235\242\347\232\204box*/\n"
"	background-color: transparent;\n"
"	border: 0px solid transparent;\n"
"}\n"
"#main_page_container{\n"
"	/*\345\217\263\344\276\247\351\241\265\351\235\242\347\232\204box*/\n"
"	background-color: transparent;\n"
"	border: 0px solid transparent;\n"
"}\n"
"\n"
"\n"
"/*-----------------------------------------------------------------------------------------------------*/\n"
"/*\344\270\273\350\246\201\351\241\265\351\235\242\347\232\204\346\240\267\345\274\217\350\241\250*/\n"
"/*-----------------------------------------------------------------------------------------------------*/\n"
"\n"
".QFrame#page_tab_box{\n"
"/*\347\224\265\350\267\257\345\233\276\346\224\276\347\275\256Tab\351\241\265\351\235\242\347\232\204box*/\n"
"	background-color: transparent;\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"	border: 0px;\n"
"}\n"
"\n"
".QWidget#page_tab_container{\n"
"/*Tab widget\347\232\204\345\256\271\345\231\250*/\n"
"	backgroun"
                        "d-color: transparent;\n"
"	border: 0px solid transparent;\n"
"	border-radius: 6px;\n"
"}\n"
"\n"
"/*.QWidget#page_tab_widget{\n"
"Tab widget\347\232\204\344\270\273\344\275\223\357\274\214qss\345\272\224\345\275\223\347\224\261\345\205\266\346\234\254\350\272\253\345\256\214\346\210\220\n"
"}*/\n"
"\n"
"#elec_view_box{\n"
"background-color: transparent;\n"
"border: 0px;\n"
"}\n"
"#elec_view_container{/*Page Container*/\n"
"background-color: transparent;\n"
"border: 0px solid transparent;\n"
"border-radius: 0px;\n"
"}\n"
"/*\347\211\271\344\276\213\347\224\265\350\267\257\345\233\276\347\232\204\346\240\267\345\274\217\350\241\250*/\n"
"#elec_view{\n"
"background-color: rgb(253, 253, 253);\n"
"border: 0px solid transparent;\n"
"border-radius: 0px;\n"
"padding: 4px;\n"
"}\n"
"\n"
"/*-----------------------------------------------------------------------------------------------------*/\n"
"/*\351\241\265\351\235\242\347\232\204splliter*/\n"
"/*----------------------------------------------------------------------"
                        "-------------------------------*/\n"
"#page_info_spliter::handle {	\n"
"	background-color: transparent;\n"
"	border: 0px;\n"
"	margin: 0px;\n"
"}\n"
"#page_info_spliter::handle:hover   {\n"
"	background-color: #93a1a1;\n"
"}\n"
"#page_info_spliter::handle:pressed   {\n"
"	background-color: #93a1a1;\n"
"}\n"
"\n"
"\n"
"/*-----------------------------------------------------------------------------------------------------*/\n"
"/*\344\270\213\346\226\271info\347\273\204\344\273\266\347\232\204\346\240\267\345\274\217\350\241\250*/\n"
"/*-----------------------------------------------------------------------------------------------------*/\n"
"#info_tab_box{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"#info_tab_container{\n"
"	background-color: transparent;\n"
"	border: 0px solid transparent;\n"
"	\n"
"}\n"
"\n"
"/*#info_tab_widget{}/*\n"
"/*Tab widget\347\232\204\344\270\273\344\275\223\357\274\214qss\345\272\224\345\275\223\347\224\261\345\205\266\346\234\254\350\272\253\345\256\214\346\210\220*/"));
        main_page_box->setFrameShape(QFrame::StyledPanel);
        main_page_box->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(main_page_box);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        main_page_container = new QWidget(main_page_box);
        main_page_container->setObjectName(QString::fromUtf8("main_page_container"));
        verticalLayout_5 = new QVBoxLayout(main_page_container);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        page_info_spliter = new QSplitter(main_page_container);
        page_info_spliter->setObjectName(QString::fromUtf8("page_info_spliter"));
        page_info_spliter->setOrientation(Qt::Vertical);
        page_info_spliter->setHandleWidth(1);
        page_tab_box = new QFrame(page_info_spliter);
        page_tab_box->setObjectName(QString::fromUtf8("page_tab_box"));
        page_tab_box->setStyleSheet(QString::fromUtf8(""));
        page_tab_box->setFrameShape(QFrame::StyledPanel);
        page_tab_box->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(page_tab_box);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        page_tab_container = new QWidget(page_tab_box);
        page_tab_container->setObjectName(QString::fromUtf8("page_tab_container"));
        verticalLayout_3 = new QVBoxLayout(page_tab_container);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        page_tab_widget = new TabPagesWidget(page_tab_container);
        page_tab_widget->setObjectName(QString::fromUtf8("page_tab_widget"));

        verticalLayout_3->addWidget(page_tab_widget);


        verticalLayout->addWidget(page_tab_container);

        page_info_spliter->addWidget(page_tab_box);
        info_tab_box = new QFrame(page_info_spliter);
        info_tab_box->setObjectName(QString::fromUtf8("info_tab_box"));
        info_tab_box->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_8 = new QHBoxLayout(info_tab_box);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        info_tab_container = new QWidget(info_tab_box);
        info_tab_container->setObjectName(QString::fromUtf8("info_tab_container"));
        horizontalLayout_3 = new QHBoxLayout(info_tab_container);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        info_tab_widget = new TabPagesWidget(info_tab_container);
        info_tab_widget->setObjectName(QString::fromUtf8("info_tab_widget"));

        horizontalLayout_3->addWidget(info_tab_widget);


        horizontalLayout_8->addWidget(info_tab_container);

        page_info_spliter->addWidget(info_tab_box);

        verticalLayout_5->addWidget(page_info_spliter);


        verticalLayout_4->addWidget(main_page_container);


        horizontalLayout_7->addWidget(main_page_box);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Chip Simulator", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actiontxt->setText(QCoreApplication::translate("MainWindow", "txt", nullptr));
        open_name_tbtn->setText(QCoreApplication::translate("MainWindow", "\345\261\225\345\274\200", nullptr));
        home_tbtn->setText(QCoreApplication::translate("MainWindow", "\344\270\273\351\241\265", nullptr));
        open_page_tbtn->setText(QCoreApplication::translate("MainWindow", "\347\273\204\344\273\266", nullptr));
        open_file_tbtn->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        component_tbtn->setText(QCoreApplication::translate("MainWindow", "\347\273\204\344\273\266", nullptr));
        component_tbtn_2->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\351\241\265", nullptr));
        settings_tbtn->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
