/**
*    @file:    flattabwidget.cpp
*    @brief:   tab的主控以及全部的页面+tab栏显示
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-05-18  09:28
*/

#ifndef TABPAGESWIDGET_H
#define TABPAGESWIDGET_H

#include <QApplication>
#include <QBoxLayout>
#include <QEasingCurve>
#include <QMap>
#include <QPalette>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QWidget>

#include "3rdparty/StackedWidgetAnimation/StackedWidgetAnimation.h"

#include "tabitem.h"
#include "tabpagegenerator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TabPagesWidget; }
QT_END_NAMESPACE


class TabPagesWidget : public QWidget
{
    Q_OBJECT
public:
    TabPagesWidget(QWidget *parent = nullptr);
    ~TabPagesWidget();

private slots:
    void foucusTab(TabItem* targetTab);
    void closeTab(TabItem* targetTab);

    void scrollDown();
    void scrollUp();

    void on_add_dea_page_btn_clicked();

public:
    bool addPage(QWidget *page);
    bool removePage(QWidget* page);

    bool removePage(TabItem* tabItem);

    TabPageGenerator *pageGen() const;
    void setPageGen(TabPageGenerator *newPageGen);

private:
    void init();
    void changePageFocus(TabItem* newFocus);

private:
    Ui::TabPagesWidget *ui;
    TabPageGenerator* _pageGen;

    TabItem* _curFocus;
    QVector<TabItem*> _tabPageVec;

    WAF::AbstractAnimator* _pageFadeInAni = nullptr;//页面渐入动画器
};

#endif // TABPAGESWIDGET_H

