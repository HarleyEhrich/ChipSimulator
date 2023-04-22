#include "AmtlGraphicsScene.h"


void AmtlGraphicsScene::pairUniConnectionPoint(bool linkStatus, UniConnectionPointPtr target)
{
    //保证在下列过程中对象不会被释放掉。
    auto firSharedPtr = _firstPair.lock();
    auto secSharedPtr = target.lock();

    if(target.isNull()) return;

    if(linkStatus == false){
        //只能是取消绑定
        if(secSharedPtr.data() == firSharedPtr.data()){//Reference to the same connetion point.
            _firstPair.clear();
        }
        secSharedPtr->update();
    }else{
        if(_firstPair.isNull()){
            //First pair to this
            _firstPair = target;
        }else{
            if(!firSharedPtr->bindConnectionPoint(secSharedPtr.data())){
                //Bind fail
                firSharedPtr->update();
                secSharedPtr->update();
            }
            _firstPair.clear();
        }
    }
}

AmtlGraphicsScene::AmtlGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{

}



void AmtlGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);
    QGraphicsScene::drawBackground(painter,rect);
//    static QPen linePen;
//    linePen.setColor(QColor(60,60,60,120));
//    linePen.setWidth(0);
//    linePen.setStyle(Qt::DashLine);

//    static int lineSpace =64;

//    qreal left=rect.left();
//    qreal right=rect.right();
//    qreal top=rect.top();
//    qreal bottom=rect.bottom();

//    painter->save();
//    painter->setRenderHint(QPainter::Antialiasing);//抗锯齿

//    painter->setPen(linePen);

//    //绘制横线
//    if(abs(top)>abs(bottom)){
//        //主体偏上
//        for(int i=0; i>=top ;i-=lineSpace){
//            painter->drawLine(left,i,right,i);
//            painter->drawLine(left,-i,right,-i);
//        }
//    }else{
//        for(int i=0; i<=bottom ;i+=lineSpace){
//            painter->drawLine(left,-i,right,-i);
//            painter->drawLine(left,i,right,i);
//        }
//    }

//    //绘制竖线

//    if(abs(left)>abs(right)){
//        //主体偏左
//        for(int i=0; i>=left;i-=lineSpace)
//        {
//            painter->drawLine(i,top,i,bottom);
//            painter->drawLine(-i,top,-i,bottom);
//        }
//    }else{
//        for(int i=0;i<=right;i+=lineSpace)
//        {
//            painter->drawLine(i,top,i,bottom);
//            painter->drawLine(-i,top,-i,bottom);
//        }
//    }
//    painter->restore();
}

void AmtlGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void AmtlGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void AmtlGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void AmtlGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}


bool AmtlGraphicsScene::registerUniConnectionPoint(UniConnectionPoint *target)
{
    if(target == nullptr) return false;

    connect(target,&UniConnectionPoint::tellBindStatusChange,this,&AmtlGraphicsScene::pairUniConnectionPoint);
    return true;
}

void AmtlGraphicsScene::makeToastInfo(QString infoTitle, QString info, bool autoHide, AMTL::ToastInfoPosition showPos, AMTL::ToastInfoType infoType)
{
    //Re pos this to mainwindow to show this toast info
    emit requestToastInfo(infoTitle,info,autoHide,showPos,infoType);
}


