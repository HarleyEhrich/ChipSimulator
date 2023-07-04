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
#include <QLayout>
#include <QGraphicsDropShadowEffect>

#include <GlobalInclude.h>

#include "Include/AniInclude.h"
#include "TabItem.h"
#include "TabBarGenerator.h"
#include "CustomTabBar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TabPagesWidget; }
QT_END_NAMESPACE


class TabPagesWidget : public QWidget
{
    Q_OBJECT
public:
    TabPagesWidget(QWidget *parent = nullptr);
    ~TabPagesWidget();

signals:
    void pageFocusChange();

private slots:
    void foucusTab(TabItem* targetTab);
    void closeTab(TabItem* targetTab);

    void scrollDown();
    void scrollUp();

    void on_add_dea_page_btn_clicked();

public:
    bool addPage(QWidget *page);

    TabPageGenerator *pageGen() const;
    void setPageGen(TabPageGenerator *newPageGen);

private:
    void init();

    bool removePage(TabItem* tabItem);

    void changePageFocus(TabItem* newFocus);

    TabItem* findTabByPage(QWidget* page);

private:
    Ui::TabPagesWidget *ui;
    QGraphicsDropShadowEffect* _eff;
    TabPageGenerator* _pageGen;
    TabItem* _curFocus;
    QVector<TabItem*> _tabPageVec;

};

#endif // TABPAGESWIDGET_H

