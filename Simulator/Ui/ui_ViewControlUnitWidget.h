/********************************************************************************
** Form generated from reading UI file 'ViewControlUnitWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWCONTROLUNITWIDGET_H
#define UI_VIEWCONTROLUNITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewControlUnitWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QFrame *container;
    QHBoxLayout *horizontalLayout;
    QToolButton *lock_view_tbtn;
    QToolButton *model_tbtn;
    QFrame *line;
    QToolButton *align_top_tbtn;
    QToolButton *align_middle_tbtn;
    QToolButton *align_bottom_tbtn;
    QToolButton *align_start_tbtn;
    QToolButton *align_center_tbtn;
    QToolButton *align_end_tbtn;
    QFrame *line_2;
    QToolButton *zoom_in_tbtn;
    QDoubleSpinBox *scale_ratio_dsp;
    QToolButton *zoom_out_tbtn;

    void setupUi(QWidget *ViewControlUnitWidget)
    {
        if (ViewControlUnitWidget->objectName().isEmpty())
            ViewControlUnitWidget->setObjectName(QString::fromUtf8("ViewControlUnitWidget"));
        ViewControlUnitWidget->resize(534, 46);
        QFont font;
        font.setFamilies({QString::fromUtf8("HarmonyOS Sans")});
        font.setPointSize(10);
        ViewControlUnitWidget->setFont(font);
        ViewControlUnitWidget->setLayoutDirection(Qt::LeftToRight);
        ViewControlUnitWidget->setStyleSheet(QString::fromUtf8("#container{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border: 0px;\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"#container .QToolButton{\n"
"	background-color: transparent;\n"
"	border: 1px transparent;\n"
"	border-radius: 4px;\n"
"	padding: 8px 8px 8px 8px;\n"
"}\n"
"\n"
"#container .QToolButton:hover{\n"
"	background-color: rgba(231, 231, 231,220);\n"
"}\n"
"\n"
"#container .QDoubleSpinBox{\n"
"	background-color: transparent;\n"
"	border-radius: 4px;\n"
"	padding-top: 4px;\n"
"	padding-bottom: 4px;\n"
"	width: 48px;\n"
"}\n"
"\n"
".QFrame#line, .QFrame#line_2{\n"
"	background-color:  gray;\n"
"	border: 0px;;\n"
"	margin-top: 8px;\n"
"	margin-bottom: 8px;\n"
"}\n"
"\n"
"\n"
"#container .QToolButton#lock_view_tbtn:checked{\n"
"	background-color: #ea5455;\n"
"	border-color: #ea5455;\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));
        horizontalLayout_2 = new QHBoxLayout(ViewControlUnitWidget);
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        container = new QFrame(ViewControlUnitWidget);
        container->setObjectName(QString::fromUtf8("container"));
        container->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("HarmonyOS Sans")});
        container->setFont(font1);
        container->setContextMenuPolicy(Qt::NoContextMenu);
        container->setLayoutDirection(Qt::LeftToRight);
        container->setFrameShape(QFrame::StyledPanel);
        container->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(container);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(8, 4, 8, 4);
        lock_view_tbtn = new QToolButton(container);
        lock_view_tbtn->setObjectName(QString::fromUtf8("lock_view_tbtn"));
        lock_view_tbtn->setMinimumSize(QSize(38, 38));
        lock_view_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/unlock.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/lock.png"), QSize(), QIcon::Normal, QIcon::On);
        lock_view_tbtn->setIcon(icon);
        lock_view_tbtn->setIconSize(QSize(18, 18));
        lock_view_tbtn->setCheckable(true);
        lock_view_tbtn->setChecked(false);

        horizontalLayout->addWidget(lock_view_tbtn);

        model_tbtn = new QToolButton(container);
        model_tbtn->setObjectName(QString::fromUtf8("model_tbtn"));
        model_tbtn->setMinimumSize(QSize(38, 38));
        model_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/move_model.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/select_model.png"), QSize(), QIcon::Normal, QIcon::On);
        model_tbtn->setIcon(icon1);
        model_tbtn->setIconSize(QSize(18, 18));
        model_tbtn->setCheckable(true);
        model_tbtn->setChecked(true);
        model_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout->addWidget(model_tbtn);

        line = new QFrame(container);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(1, 0));
        line->setMaximumSize(QSize(1, 16777215));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(1);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::VLine);

        horizontalLayout->addWidget(line);

        align_top_tbtn = new QToolButton(container);
        align_top_tbtn->setObjectName(QString::fromUtf8("align_top_tbtn"));
        align_top_tbtn->setMinimumSize(QSize(38, 38));
        align_top_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/aligin_top.png"), QSize(), QIcon::Normal, QIcon::Off);
        align_top_tbtn->setIcon(icon2);
        align_top_tbtn->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(align_top_tbtn);

        align_middle_tbtn = new QToolButton(container);
        align_middle_tbtn->setObjectName(QString::fromUtf8("align_middle_tbtn"));
        align_middle_tbtn->setMinimumSize(QSize(38, 38));
        align_middle_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/align_center.png"), QSize(), QIcon::Normal, QIcon::Off);
        align_middle_tbtn->setIcon(icon3);
        align_middle_tbtn->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(align_middle_tbtn);

        align_bottom_tbtn = new QToolButton(container);
        align_bottom_tbtn->setObjectName(QString::fromUtf8("align_bottom_tbtn"));
        align_bottom_tbtn->setMinimumSize(QSize(38, 38));
        align_bottom_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/align_bottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        align_bottom_tbtn->setIcon(icon4);
        align_bottom_tbtn->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(align_bottom_tbtn);

        align_start_tbtn = new QToolButton(container);
        align_start_tbtn->setObjectName(QString::fromUtf8("align_start_tbtn"));
        align_start_tbtn->setMinimumSize(QSize(38, 38));
        align_start_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/align_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        align_start_tbtn->setIcon(icon5);
        align_start_tbtn->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(align_start_tbtn);

        align_center_tbtn = new QToolButton(container);
        align_center_tbtn->setObjectName(QString::fromUtf8("align_center_tbtn"));
        align_center_tbtn->setMinimumSize(QSize(38, 38));
        align_center_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/align_mid.png"), QSize(), QIcon::Normal, QIcon::Off);
        align_center_tbtn->setIcon(icon6);
        align_center_tbtn->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(align_center_tbtn);

        align_end_tbtn = new QToolButton(container);
        align_end_tbtn->setObjectName(QString::fromUtf8("align_end_tbtn"));
        align_end_tbtn->setMinimumSize(QSize(38, 38));
        align_end_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/align_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        align_end_tbtn->setIcon(icon7);
        align_end_tbtn->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(align_end_tbtn);

        line_2 = new QFrame(container);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMinimumSize(QSize(1, 0));
        line_2->setMaximumSize(QSize(1, 16777215));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        zoom_in_tbtn = new QToolButton(container);
        zoom_in_tbtn->setObjectName(QString::fromUtf8("zoom_in_tbtn"));
        zoom_in_tbtn->setMinimumSize(QSize(38, 38));
        zoom_in_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoom_in_tbtn->setIcon(icon8);
        zoom_in_tbtn->setIconSize(QSize(18, 18));
        zoom_in_tbtn->setCheckable(false);
        zoom_in_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        zoom_in_tbtn->setAutoRaise(false);

        horizontalLayout->addWidget(zoom_in_tbtn);

        scale_ratio_dsp = new QDoubleSpinBox(container);
        scale_ratio_dsp->setObjectName(QString::fromUtf8("scale_ratio_dsp"));
        scale_ratio_dsp->setMaximumSize(QSize(40, 16777215));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("HarmonyOS Sans")});
        font2.setPointSize(10);
        font2.setUnderline(false);
        scale_ratio_dsp->setFont(font2);
        scale_ratio_dsp->setWrapping(true);
        scale_ratio_dsp->setAlignment(Qt::AlignCenter);
        scale_ratio_dsp->setButtonSymbols(QAbstractSpinBox::NoButtons);
        scale_ratio_dsp->setAccelerated(false);
        scale_ratio_dsp->setProperty("showGroupSeparator", QVariant(false));
        scale_ratio_dsp->setDecimals(2);
        scale_ratio_dsp->setMinimum(0.300000000000000);
        scale_ratio_dsp->setMaximum(8.000000000000000);
        scale_ratio_dsp->setSingleStep(0.100000000000000);
        scale_ratio_dsp->setValue(1.000000000000000);

        horizontalLayout->addWidget(scale_ratio_dsp);

        zoom_out_tbtn = new QToolButton(container);
        zoom_out_tbtn->setObjectName(QString::fromUtf8("zoom_out_tbtn"));
        zoom_out_tbtn->setMinimumSize(QSize(38, 38));
        zoom_out_tbtn->setMaximumSize(QSize(38, 38));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/vcu_icon/ViewControllUnitIcon/zoom-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoom_out_tbtn->setIcon(icon9);
        zoom_out_tbtn->setIconSize(QSize(18, 18));
        zoom_out_tbtn->setCheckable(false);
        zoom_out_tbtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        zoom_out_tbtn->setAutoRaise(false);

        horizontalLayout->addWidget(zoom_out_tbtn);


        horizontalLayout_2->addWidget(container);


        retranslateUi(ViewControlUnitWidget);

        QMetaObject::connectSlotsByName(ViewControlUnitWidget);
    } // setupUi

    void retranslateUi(QWidget *ViewControlUnitWidget)
    {
        ViewControlUnitWidget->setWindowTitle(QCoreApplication::translate("ViewControlUnitWidget", "Form", nullptr));
#if QT_CONFIG(tooltip)
        lock_view_tbtn->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        lock_view_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "\351\224\201\345\256\232", nullptr));
#if QT_CONFIG(tooltip)
        model_tbtn->setToolTip(QCoreApplication::translate("ViewControlUnitWidget", "\347\247\273\345\212\250\346\250\241\345\274\217", nullptr));
#endif // QT_CONFIG(tooltip)
        model_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "\346\233\264\345\244\232", nullptr));
        align_top_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "...", nullptr));
        align_middle_tbtn->setText(QString());
        align_bottom_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "...", nullptr));
        align_start_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "...", nullptr));
        align_center_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "...", nullptr));
        align_end_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "...", nullptr));
#if QT_CONFIG(tooltip)
        zoom_in_tbtn->setToolTip(QCoreApplication::translate("ViewControlUnitWidget", "\347\274\251\345\260\217\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
        zoom_in_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "\346\224\276\345\244\247", nullptr));
        scale_ratio_dsp->setSuffix(QCoreApplication::translate("ViewControlUnitWidget", "%", nullptr));
#if QT_CONFIG(tooltip)
        zoom_out_tbtn->setToolTip(QCoreApplication::translate("ViewControlUnitWidget", "\346\224\276\345\244\247\350\247\206\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
        zoom_out_tbtn->setText(QCoreApplication::translate("ViewControlUnitWidget", "\347\274\251\345\260\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewControlUnitWidget: public Ui_ViewControlUnitWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWCONTROLUNITWIDGET_H
