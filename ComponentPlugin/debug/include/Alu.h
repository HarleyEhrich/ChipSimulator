#ifndef ALU_H
#define ALU_H

#include <QBrush>
#include <QPen>
#include <QSize>

#include <GlobalInclude.h>
#include <abstractconinterface.h>

class Alu : public AbstractConInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AbstractConInterface_iid FILE "Alu.json")
    Q_INTERFACES(AbstractConInterface)
public:
    explicit Alu():
        AbstractConInterface(){
        init();
    }
    explicit Alu(long sceneID, QGraphicsItem *parent = nullptr, QObject* parentObject=nullptr):
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
                                "Alu",
                                "",
                                "Bulid In",
                                "2023-05-01",
                                ""//todo image path not set
                                );
        }


        _comName = "";

        _mSig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::LEFT,
                                    false,
                                    "M")
            );
        _mSig.lock()->setTextDirection(TextDriection::RIGHT);
        _mSig.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() /2, -65);


        _cnSig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::RIGHT,
                                    false,
                                    "CN")
            );
        _cnSig.lock()->setTextDirection(TextDriection::LEFT);
        _cnSig.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() /2, 65);


        _s0Sig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::LEFT,
                                    false,
                                    "S0")
            );
        _s0Sig.lock()->setTextDirection(TextDriection::RIGHT);
        _s0Sig.lock()->setPos( - __mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() /2, 0);

        _s1Sig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::LEFT,
                                    false,
                                    "S1")
            );
        _s1Sig.lock()->setTextDirection(TextDriection::RIGHT);
        _s1Sig.lock()->setPos( - __mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() /2, 65);

        _s2Sig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::RIGHT,
                                    false,
                                    "S2")
            );

        _s2Sig.lock()->setTextDirection(TextDriection::LEFT);
        _s2Sig.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() /2, -65);

        _s3Sig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::RIGHT,
                                    false,
                                    "S3")
            );
        _s3Sig.lock()->setTextDirection(TextDriection::LEFT);
        _s3Sig.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() /2, 0);


        _cySig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::ABOVE,
                                    true,
                                    "CY")
            );

        _cySig.lock()->setTextDirection(TextDriection::ABOVE);
        _cySig.lock()->setPos(0, - __mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH()/2);

        _ziSig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::ABOVE,
                                    true,
                                    "ZI")
            );
        _ziSig.lock()->setTextDirection(TextDriection::ABOVE);
        _ziSig.lock()->setPos(-UniConnectionPoint::mainBodyWH()*2,  - __mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH()/2);


        _arSig = getCCPointWPtrById(
            RegisterConnectionPoint(this,
                                    COOR_POS::ABOVE,
                                    false,
                                    "AR")
            );
        _arSig.lock()->setTextDirection(TextDriection::ABOVE);
        _arSig.lock()->setPos(-UniConnectionPoint::mainBodyWH()*4,  - __mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH()/2);


        int startX = - __mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH()/2 + 24;
        int spaceer = 8 + UniConnectionPoint::mainBodyWH();

        UniConnectionPointPtr op1,op2,out;
        for(int i=0;i<8;++i){
            op1 = getCCPointWPtrById(
                RegisterConnectionPoint(this,
                                        COOR_POS::BELOW,
                                        false,
                                        QString::number(i))
                );
            op2 = getCCPointWPtrById(
                RegisterConnectionPoint(this,
                                        COOR_POS::BELOW,
                                        false,
                                        QString::number(i))
                );
            out = getCCPointWPtrById(
                RegisterConnectionPoint(this,
                                        COOR_POS::ABOVE,
                                        true,
                                        QString::number(i))
                );
            op1.lock()->setTextDirection(TextDriection::ABOVE);
            op2.lock()->setTextDirection(TextDriection::ABOVE);

            op1.lock()->setPos(startX,__mainBodySizeHalf.height() + UniConnectionPoint::mainBodyWH() /2);
            op2.lock()->setPos(-startX,__mainBodySizeHalf.height() + UniConnectionPoint::mainBodyWH() /2) ;
            out.lock()->setPos(-startX,-__mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH() /2);

            op1Vec.push_back(op1);
            op2Vec.push_back(op2);
            outVec.push_back(out);

            startX += spaceer;
        }

        runImpl();

        connect(this,&Alu::tellComNickNameChange,this,&Alu::updateStatus);
        updateStatus();
    }

    int getOp1(){
        int res = 0;
        for(int i = 7; i>=0 ;--i){
            res*=2;
            res += op1Vec[i].lock()->getDataValue(0);
        }
        return res;
    }

    int getOp2(){
        int res = 0;
        for(int i = 7; i>=0 ;--i){
            res*=2;
            res += op2Vec[i].lock()->getDataValue(0);
        }
        return res;
    }

    void writeOut(int res){
        for(int i = 0; i < 8 ;++i){
            outVec[i].lock()->setDataValue(
                QBitArray{1,(bool)(res%2)},
                0);
            res/=2;
        }
    }

    inline void runImpl(){
        bool cy=_cySig.lock()->getDataValue(0);
        bool zi=_ziSig.lock()->getDataValue(0);
        bool ar=_arSig.lock()->getDataValue(0);
        bool s3=_s3Sig.lock()->getDataValue(0);
        bool s2=_s2Sig.lock()->getDataValue(0);
        bool s1=_s1Sig.lock()->getDataValue(0);
        bool s0=_s0Sig.lock()->getDataValue(0);
        bool m=_mSig.lock()->getDataValue(0);
        bool cn=_cnSig.lock()->getDataValue(0);

        int dr1=getOp1();
        int dr2=getOp2();

        int res=0;
        if (ar) {
            cy = false;
            zi = false;
        }

        if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//dr1
            res = dr1;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//dr1+1
            res = dr1 + 1;
            if (ar && res>255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 1) {//逻辑  ~dr1
            res = 256 - dr1;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {// dr1|dr2
            res = dr1 | dr2;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {// dr1|dr2+1
            res = dr1 | dr2 + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 1) {//逻辑 ~(dr1|dr2)
            res = dr1 | dr2;
            res = 256-res;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//A|(~B)
            res = dr1 | (256-dr2);
        }
        else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//A||(~B)+1
            res = (dr1 | (256 - dr2)) + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 1) {//逻辑 ~(A|B)
            res = 256 - (dr1 | dr2);
        }
        else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//-1
            res = 255;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//0
            res = 0;
        }
        else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 1) {//逻辑0
            res = 0;
        }
        else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+(A&~b)
            res = dr1 + (dr1 & (256 - dr2));
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+(A&~b)+1
            res = dr1 + (dr1 & (256 - dr2))+1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 1) {//逻辑~(a&b)
            res = 256 - (dr1 & dr2);
        }
        else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//(A|B)+(A&~B)
            res = (dr1 | dr2) + (dr1 & (256 - dr2));
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//(A|B)+(A&~B)+1
            res = (dr1 | dr2) + (dr1 & (256 - dr2)) + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 1) {//逻辑~dr2
            res = 256 - dr2;
        }
        else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//a-b-1
            res = dr1 - dr2 + 255 + 255;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//a-b
            res = dr1 - dr2+256;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;

        }
        else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 1) {//逻辑(a^b)
            res = dr1 ^ dr2;

        }
        else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//(A&~B)-1
            res = dr1 & (256 - dr2) + 255;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;

        }
        else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A&~B
            res = dr1 & (256 - dr2);
            if (ar) {
                cy = true;
            }

        }
        else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A&~B
            res = dr1 & (256 - dr2);

        }
        else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+A&B
            res = dr1 + (dr1 & dr2);
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;

        }
        else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+A&B+1
            res = dr1 + (dr1 & dr2) + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;

        }
        else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 1) {//逻辑~A | B   here
            res = 256 - (dr1 & dr2);

        }
        else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//A+B
            res = dr1 + dr2;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//A+B+1
            res = dr1 + dr2 + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 1) {//逻辑~(A^B)
            res = 256 - (dr1 ^ dr2);
        }
        else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//(A|~B)+A&B
            res = (dr1 | (256 - dr2)) + (dr1 & dr2);
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//(A|~B)+A&B+1
            res = (dr1 | (256 - dr2)) + dr1 & dr2 + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 1) {//逻辑B
            res = dr2;
        }
        else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//A&B-1
            res = dr1 & dr2 + 255;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A&B
            res = dr1 & dr2;
        }
        else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A&B
            res = dr1 & dr2;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+A
            res = dr1 + dr1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+A+1
            res = dr1 + dr1+1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 1) {//逻辑1
            res = 1;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//(A|B)+A
            res = (dr1 | dr2) + dr1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//(A|B)+A+1
            res = (dr1 | dr2) + dr1 + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 1) {//逻辑A|~B
            res = dr1 | (256 - dr2);
        }
        else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//(A|~B)+A
            res = (dr1 | (256 - dr2)) + dr1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//(A|~B)+A+1
            res = (dr1 | (256 - dr2)) + dr1 + 1;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 1) {//逻辑A|B
            res = dr1 | dr2;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//A-1
            res = dr1 + 255;
            if (ar && res > 255) {
                cy = true;
            }
            res %= 256;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A
            res = dr1;
        }
        else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A
            res = dr1;
        }
        //
        if (ar) {
            if (res == 0) {
                zi = true;
            }
            else {
                zi = false;
            }
        }


        _ziSig.lock()->setDataValue(QBitArray{1,zi},0);
        _cySig.lock()->setDataValue(QBitArray{1,cy},0);

        writeOut(res);

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

    QVector<UniConnectionPointPtr> op1Vec,op2Vec,outVec;
    UniConnectionPointPtr _mSig,_cnSig,_s0Sig,_s1Sig,_s2Sig,_s3Sig;
    UniConnectionPointPtr _cySig,_ziSig,_arSig;

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
        return new Alu(sceneID,parent);
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

        __mainBodySize.setWidth(460);
        __mainBodySize.setHeight(260);

        __mainBodySizeHalf.setWidth(230);
        __mainBodySizeHalf.setHeight(130);

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
    inline static const QString __xmlLabel{"Alu"};
    inline static bool __intialSta = false;

    inline static QSize __mainBodySize;
    inline static QSize __mainBodySizeHalf;

    inline static QPoint __textLBPos;

    inline static QColor __mainBodyColor;
    inline static QPen __mainBodyPen;
    inline static QBrush __mainBodyBrush;

};

#endif // ALU_H
