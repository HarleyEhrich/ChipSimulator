#ifndef AMTLGRAPHICSVIEW_H
#define AMTLGRAPHICSVIEW_H

#include <QDebug>
#include <QGraphicsEffect>
#include <QGraphicsView>
//#include <QLineEdit>
#include <QMouseEvent>
#include <QObject>
#include <QPaintEvent>
#include <QPushButton>
#include <QWidget>
<<<<<<< HEAD

#include "include/project_include.h"
#include "viewcontrollunit.h"
=======
#include <QLayout>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QPluginLoader>

#include "Include/ProjectInclude.h"
#include "MultiplexedScendaryWidget/ViewControlUnitWidget.h"
#include "AmtlGraphicsScene.h"
#include "abstractconinterface.h"

>>>>>>> c344d8f (修改接口)

class AmtlGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    AmtlGraphicsView(QWidget *parent = nullptr);


    // QWidget interface
protected:

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    void initial();

private:
    QPushButton* _zoomInBtn;
    QPushButton* _zoomOutBtn;
    QLineEdit* _zoomRatio;
    double _scaleRatio;

};

#endif // AMTLGRAPHICSVIEW_H
