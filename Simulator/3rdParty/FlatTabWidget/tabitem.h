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
    QWidget* getPage(){
        return _page;
    }

private:
    Ui::TabItem *ui;

    QWidget* _page;

    bool _tabFocused;


protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override{
        if(event->button() == Qt::LeftButton){
            if(_tabFocused ==false ){
                emit foucusTab(this);
            }
        }
    }

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override{
        if(event->button() == Qt::LeftButton){
            if(_tabFocused ==false ){
                emit closeTab(this);
            }
        }
    }
};

#endif // TABITEM_H
