#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>
#include <QList>
#include <QMainWindow>
#include <QTextBrowser>
#include <QWidget>
#include <QFileDialog>

#include "Widgets/FloatWidgets/ToastInfoWidget.h"
#include "include/ProjectInclude.h"

#include "ControlObj/PluginLoaderController.h"

#include "Pages/ElecPages/ElecPage.h"
#include "Pages/ElecPages/ComponentListPage.h"



#include "abstractconinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_page_info_spliter_splitterMoved(int pos, int index);


    void on_component_tbtn_clicked(bool checked);

    void on_open_file_tbtn_clicked();

private:
    void init();

    void initMenu();

private:
    Ui::MainWindow *ui;
    PluginLoaderController* _comLoader;
    ComponentListPage* _listPage;
    ElecPageGener* _elecPageGener;
};
#endif // MAINWINDOW_H
