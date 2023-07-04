#ifndef REGISTER74LS374_H
#define REGISTER74LS374_H

#include <QBrush>
#include <QPen>
#include <QSize>

#include <GlobalInclude.h>
#include <abstractconinterface.h>

class Register74LS374 : public AbstractConInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AbstractConInterface_iid FILE "Register74LS374.json")
    Q_INTERFACES(AbstractConInterface)

public:
    explicit Register74LS374():
        AbstractConInterface(){
        init();
    }
    explicit Register74LS374(long sceneID, QGraphicsItem *parent = nullptr, QObject* parentObject=nullptr):
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
                                "Register74LS374",
                                "",
                                "Bulid In",
                                "2023-05-01",
                                ""//todo image path not set
                                );
        }


        _comName = "";


        int startY = -__mainBodySizeHalf.height()+ UniConnectionPoint::mainBodyWH()/2 +4;
        int spcerInY = (__mainBodySize.height() - 8 - UniConnectionPoint::mainBodyWH()) / 8;

        int inputId;
        int outputId;
        UniConnectionPointPtr inputPtr,outputPtr;
        for(int i=0;i<8;++i){
            inputId = RegisterConnectionPoint(this,
                                              COOR_POS::LEFT,
                                              false,
                                              "A"+QString::number(i));
            outputId = RegisterConnectionPoint(this,
                                               COOR_POS::RIGHT,
                                               true,
                                               "D"+QString::number(i),
                                               1,10);

            inputPtr = getCCPointWPtrById(inputId);
            outputPtr = getCCPointWPtrById(outputId);

            inputPtr.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6,startY);
            outputPtr.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() - 6,startY);

            inputPtr.lock()->setTextDirection(TextDriection::RIGHT);
            outputPtr.lock()->setTextDirection(TextDriection::LEFT);

            _inputVec.push_back(inputPtr);
            _outputVec.push_back(outputPtr);

            startY+=spcerInY;

        }

        _clk = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::LEFT,
                                    false,
                                    "CLK")
            );

        _en = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::RIGHT,
                                    false,
                                    "!EN")
            );


        _clk.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6,
                            __mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH() - 4);
        _en.lock()->setPos( __mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() - 6,
                           __mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH() - 4);

        _clk.lock()->setTextDirection(TextDriection::RIGHT);
        _en.lock()->setTextDirection(TextDriection::LEFT);

        runImpl();

        connect(this,&Register74LS374::tellComNickNameChange,this,&Register74LS374::updateStatus);
        updateStatus();
    }

    inline void runImpl(){
        bool curClk = _clk.lock()->getDataValue(0);
        if(false == _lastTimeClk && curClk){//正跳变
            for(int i =0;i<8;++i){
                _outputVec[i].lock()->setDataValue(
                    QBitArray{1,_inputVec[i].lock()->getDataValue(0)},0
                    );
            }
        }

        if(!_en.lock()->getDataValue(0)){//Out put
            for(int i =0;i<8;++i){
                _outputVec[i].lock()->setHighResistance(false);
            }
        }else{
            for(int i =0;i<8;++i){//Stop
                _outputVec[i].lock()->setHighResistance(true);
            }
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

    UniConnectionPointPtr _clk,_en;
    QVector<UniConnectionPointPtr> _inputVec, _outputVec;

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
        return new Register74LS374(sceneID,parent);
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

        __mainBodySize.setWidth(160);
        __mainBodySize.setHeight(240);

        __mainBodySizeHalf.setWidth(80);
        __mainBodySizeHalf.setHeight(120);

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
    inline static const QString __xmlLabel{"Register74LS374"};
    inline static bool __intialSta = false;

    inline static QSize __mainBodySize;
    inline static QSize __mainBodySizeHalf;

    inline static QPoint __textLBPos;

    inline static QColor __mainBodyColor;
    inline static QPen __mainBodyPen;
    inline static QBrush __mainBodyBrush;

};

#endif // REGISTER74LS374_H
