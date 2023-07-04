#include "tabitem.h"
#include "ui_tabitem.h"

#include <QMouseEvent>
#include <QPalette>
#include <QPixmap>

TabItem::TabItem(QWidget* page , QWidget *parent) :
    QWidget(parent),
    _page(page),
    ui(new Ui::TabItem)
{
    ui->setupUi(this);

    setTitle(page->windowTitle());
    connect(page,&QWidget::windowTitleChanged,this,&TabItem::setTitle);
}

TabItem::~TabItem()
{
    delete ui;
}

void TabItem::setTitle(const QString& newTitle)
{
    ui->title->setText(newTitle);
}

void TabItem::setTabFocused(bool focused){
    _tabFocused =focused;

    //todo make somechange in qss
}

void TabItem::on_close_tbtn_clicked()
{
    emit closeTab(this);
}

QString TabItem::getTitle(){
    return ui->title->text();
}

bool TabItem::getTabFocused(){
    return _tabFocused;
}

bool TabItem::isYouPage(QWidget *page){
    return _page == page;
}


