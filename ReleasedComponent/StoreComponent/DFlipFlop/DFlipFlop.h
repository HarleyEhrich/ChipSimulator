#ifndef DFLIPFLOP_H
#define DFLIPFLOP_H

#include <QBrush>
#include <QPen>
#include <QSize>

#include <GlobalInclude.h>
#include <abstractconinterface.h>

class DFlipFlop : public AbstractConInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AbstractConInterface_iid FILE "DFlipFlop.json")
    Q_INTERFACES(AbstractConInterface)
public:
    explicit DFlipFlop():
        AbstractConInterface(){
        init();
    }
    explicit DFlipFlop(long sceneID, QGraphicsItem *parent = nullptr, QObject* parentObject=nullptr):
        AbstractConInterface(sceneID, parent, parentObject){
        init();
    }

    // AbstractConInterface interface
public slots:
    virtual void run() override{
        runImpl();
        update();
    }


public:
    QFont font() const{
        return _font;
    }

private:
    void init(){
        if(false == __intialSta){
            IntialStaticVariable();
            IntialComponentInfo(this,
                                "001",
                                "DFlipFlop",
                                "",
                                "Bulid In",
                                "2023-05-01",
                                ""//todo image path not set
                                );
        }


        _comName = "&";

        int input1 = RegisterConnectionPoint(this,
                                             COOR_POS::LEFT,
                                             false,
                                             "D");
        int input2 = RegisterConnectionPoint(this,
                                             COOR_POS::LEFT,
                                             false,
                                             "CLK");
        int output1 = RegisterConnectionPoint(this,
                                            COOR_POS::RIGHT,
                                            true,
                                            "Q",
                                            1,10);

        int output2 = RegisterConnectionPoint(this,
                                            COOR_POS::RIGHT,
                                            true,
                                            "!Q",
                                            1,10);

        _input1 = getCCPointWPtrById(input1);
        _input2 = getCCPointWPtrById(input2);
        _output1 = getCCPointWPtrById(output1);
        _output2 = getCCPointWPtrById(output2);

        _input1.lock()->setTextDirection(TextDriection::RIGHT);
        _input2.lock()->setTextDirection(TextDriection::RIGHT);
        _output1.lock()->setTextDirection(TextDriection::LEFT);
        _output2.lock()->setTextDirection(TextDriection::LEFT);

        _input1.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6 ,-__mainBodySizeHalf.height()/2);
        _input2.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6 ,__mainBodySizeHalf.height()/2);
        _output1.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() - 6,-__mainBodySizeHalf.height()/2);
        _output2.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() - 6,__mainBodySizeHalf.height()/2);

        runImpl();

        connect(this,&DFlipFlop::tellComNickNameChange,this,&DFlipFlop::updateStatus);
        updateStatus();
    }

    inline void runImpl(){
        bool curClk = _input2.lock()->getDataValue(0);
        if(false == _lastTimeClk && curClk){//正跳变
            bool curInputValue = _input1.lock()->getDataValue(0);
            _output1.lock()->setDataValue(QBitArray{1,curInputValue},0);
            _output2.lock()->setDataValue(QBitArray{1,!curInputValue},0);
        }
        _lastTimeClk = curClk;
    }

    void updateStatus(){
        gneratePos();
        gnerateItemPainterPathImpl();
    }

    void gneratePos(){
        QFontMetrics fm{_font};
        _comNameLBPos.setX(-fm.boundingRect(_comName).width()/2);
        _comNameLBPos.setY(-fm.boundingRect(_comName).height()-4);
    }

    void gnerateItemPainterPathImpl(){
        _itemPainterPath.clear();

        _itemPainterPath.addRect(-__mainBodySizeHalf.width(),-__mainBodySizeHalf.height(),__mainBodySize.width(),__mainBodySize.height());
        _itemPainterPath.addText(__textLBPos,font(),_comNickName);
        _itemPainterPath.addText(_comNameLBPos,font(),_comName);


        //Add the bouding rect
        for(auto&ccpItem : getCCPointVec()){
            QRectF ccPointRect = ccpItem->getRealBoudingRect();
            ccPointRect.moveCenter(
                mapFromScene(
                    ccpItem->getRealItemCenterScenePos()
                    )
                );
            _itemPainterPath.addRect(ccPointRect);
        }


        QRect bouding = _itemPainterPath.boundingRect().toRect();

        bouding.moveTopLeft({bouding.x() - 8,bouding.y() - 8});
        bouding.setHeight(bouding.height() + 16);
        bouding.setWidth(bouding.width() + 16);

        prepareGeometryChange();

        _boudingRect = bouding;

        update();
    }

private:
    QString _comName;
    QPoint _comNameLBPos;
    QFont _font;

    bool _lastTimeClk = false;

    UniConnectionPointPtr _input1,_input2,_output1,_output2;

public:
    // QGraphicsItem interface
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override{
        Q_UNUSED(option)
        Q_UNUSED(widget)

        painter->save();

        RENDER_HINT_ANT(painter);

        painter->setFont(font());
        painter->drawText(__textLBPos,_comNickName);
        painter->drawText(_comNameLBPos,_comName);

        painter->setPen(__mainBodyPen);
        painter->setBrush(__mainBodyBrush);
        painter->drawRoundedRect(-__mainBodySizeHalf.width(),
                                 -__mainBodySizeHalf.height(),
                                 __mainBodySize.width(),
                                 __mainBodySize.height(),4,4);

        painter->restore();
    }


protected:
    virtual AbstractConInterface *instanceImpl(long sceneID, QGraphicsItem *parent) override{
        return new DFlipFlop(sceneID,parent);
    }

    virtual void gnerateItemPainterPath() override{
        gnerateItemPainterPathImpl();
    }

    virtual bool loadFromXmlExtendImpl(QXmlStreamReader *root) override{
        Q_UNUSED(root);
        return true;
    }

    virtual bool saveToXmlExtendImpl(QXmlStreamWriter *root) override{
        Q_UNUSED(root);
        return true;
    }

    virtual void connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen) override{
        Q_UNUSED(changePtr);
        Q_UNUSED(changedIndex);
        Q_UNUSED(changeLen);

        run();
    }


private:
    static void IntialStaticVariable(){
        if(__intialSta) return ;

        __mainBodySize.setWidth(80);
        __mainBodySize.setHeight(120);

        __mainBodySizeHalf.setWidth(40);
        __mainBodySizeHalf.setHeight(60);

        __textLBPos.setX(-__mainBodySizeHalf.width());
        __textLBPos.setY(-__mainBodySizeHalf.height()-8);


        __mainBodyColor.setRgb(255, 255, 255);//Pure white
        __mainBodyPen.setColor(__mainBodyColor);
        __mainBodyPen.setWidth(0);
        __mainBodyBrush.setColor(__mainBodyColor);
        __mainBodyBrush.setStyle(Qt::BrushStyle::SolidPattern);

        __intialSta = true;
    }

private:
    inline static const QString __xmlLabel{"DFlipFlop"};
    inline static bool __intialSta = false;

    inline static QSize __mainBodySize;
    inline static QSize __mainBodySizeHalf;

    inline static QPoint __textLBPos;

    inline static QColor __mainBodyColor;
    inline static QPen __mainBodyPen;
    inline static QBrush __mainBodyBrush;

};

#endif // DFLIPFLOP_H
