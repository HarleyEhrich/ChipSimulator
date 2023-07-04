#ifndef TABITEM_H
#define TABITEM_H

/**
*    @file:    tabitem.h
*    @brief:   tab的显示使用的小组件
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-05-18  09:22
*/


#include <QMouseEvent>
#include <QTimer>
#include <QWidget>

namespace Ui {
class TabItem;
}

class TabItem : public QWidget
{
    Q_OBJECT

public:
    explicit TabItem(QWidget* page =nullptr, QWidget *parent = nullptr);
    ~TabItem();
signals:
    void foucusTab(TabItem* tagerTab);
    void closeTab(TabItem* tagerTab);

public slots:
    void setTitle(const QString& newTitle);
    void setTabFocused(bool focused);

private slots:
    void on_close_tbtn_clicked();


public:
    QString getTitle();
    bool getTabFocused();

    bool isYouPage(QWidget* page);
    QWidget* getPage();

private:
    Ui::TabItem *ui;

    QWidget* _page;

    bool _tabFocused;


protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};


#define UNFOCUS_STYLE \
"#box{\
    background-color: #f3f3f3;\
    border: 0px;\
    border-radius:4px;\
    margin: 2px;\
    padding: 2px;\
}\
#box:hover{\
    background-color: rgba(0, 43, 91, 180);\
    color: rgb(238, 238, 238);\
}\
#container .QToolButton{\
    background-color: transparent;\
    border: 1px transparent;\
    border-radius: 2px;\
    padding: 2px 2px 2px 2px;\
}\
#container .QToolButton:hover{\
    background-color: rgba(231, 231, 231,220);\
}\
#title{\
    font: 400 10pt \"思源黑体 CN Normal\";\
min-width: 48px;\
}"


#define FOCUS_STYLE \
"#box{\
    background-color: #002b5b;\
    border: 0px;\
    border-radius:4px;\
    margin: 2px;\
    padding: 2px;\
}\
#box:hover{\
    background-color: rgba(0, 43, 91, 180);\
    color: rgb(238, 238, 238);\
}\
#container .QToolButton{\
    background-color: transparent;\
    border: 1px transparent;\
    border-radius: 2px;\
    padding: 2px 2px 2px 2px;\
}\
#container .QToolButton:hover{\
    background-color: rgba(231, 231, 231,220);\
}\
#title{\
    font: 400 10pt \"思源黑体 CN Normal\";\
    min-width: 48px;\
    color: rgb(238, 238, 238);\
}"


#endif // TABITEM_H
