#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QGraphicsDropShadowEffect>

=======
#include <QTextBrowser>
#include <QWidget>
#include <QFileDialog>

#include "Widgets/FloatWidgets/ToastInfoWidget.h"
#include "include/ProjectInclude.h"

#include "ControlObj/ElecGraphicsControllor.h"


#include "abstractconinterface.h"
>>>>>>> c344d8f (修改接口)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

<<<<<<< HEAD
private:
    Ui::MainWindow *ui;

    QGraphicsDropShadowEffect* _sidebarShadow;
    QGraphicsDropShadowEffect* _mainContentShadow;
=======
private slots:
    void on_page_info_spliter_splitterMoved(int pos, int index);


    void on_component_tbtn_clicked();

private:
    void init();

    void initMenu();

private:
    Ui::MainWindow *ui;

    QVector<ElecGraphicsControllor*> _controlVec;
>>>>>>> c344d8f (修改接口)
};
#endif // MAINWINDOW_H
