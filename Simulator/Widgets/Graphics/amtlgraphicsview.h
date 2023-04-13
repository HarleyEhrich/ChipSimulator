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

#include "include/project_include.h"
#include "viewcontrollunit.h"

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
