#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>
#include <QList>
#include <QMainWindow>
#include <QTextBrowser>
#include <QWidget>

#include "include/ProjectInclude.h"

#include "Widgets/Graphics/AmtlGraphicsScene.h"
#include "Widgets/Graphics/AmtlGraphicsView.h"

#include "Widgets/FloatWidgets/ToastInfoWidget.h"

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


private:
    void init();

    void initMenu();

private:
    Ui::MainWindow *ui;

//    QGraphicsDropShadowEffect* _sidebarShadow;
//    QGraphicsDropShadowEffect* _pageStackWidgetContainerShadow;
};
#endif // MAINWINDOW_H
