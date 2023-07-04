#ifndef ELECPAGE_H
#define ELECPAGE_H

#include <QWidget>
#include <QFileDialog>

#include <Widgets/PageWidget/TabBarGenerator.h>

#include "ControlObj/ElecSceneViewController.h"

namespace Ui {
class ElectPage;
}

class ElecPage;
class ElecPageController;
class ElecPageGener;

class ElecPage : public QWidget
{
    Q_OBJECT

    friend class ElecPageController;

public:
    explicit ElecPage(QWidget *parent = nullptr);
    ~ElecPage();

private slots:
    void on_new_project_btn_clicked();

    void on_open_project_btn_clicked();

private:
    Ui::ElectPage *ui;
    ElecSceneViewControllerSPtr _elecViewSceneControllerSPtr;
};
MAKE_AUTO_PTR(ElecPage);


class ElecPageGener : public QObject , public TabPageGenerator{
    Q_OBJECT
public slots:

    // TabPageGenerator interface
public:
    virtual QWidget *page() override;
};

#endif // ELECPAGE_H
