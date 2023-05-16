#ifndef SWITCHCOMPONENT_H
#define SWITCHCOMPONENT_H


#include <GlobalInclude.h>
#include <abstractconinterface.h>

class SwitchComponent : public AbstractConInterface{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AbstractConInterface_iid FILE "Switch.json")
    Q_INTERFACES(AbstractConInterface)

public:
    explicit SwitchComponent();

    explicit SwitchComponent(long sceneID, QGraphicsItem *parent = nullptr, QObject* parentObject=nullptr);

    virtual ~SwitchComponent();

signals:
    void tellStatusChange(bool newStatus);

public slots:
    void updateAllStatus();


    // AbstractConInterface interface
public slots:
    virtual void run() override;


public:
    bool switchStatus() const;
    void setSwitchStatus(bool newSwitchStatus);

private:
    void initial();

    void gnerateItemPainterPathImpl();

private:
    bool _switchStatus;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual AbstractConInterface *instanceImpl(long sceneID, QGraphicsItem *parent) override;
    virtual void gnerateItemPainterPath() override;
    virtual bool loadFromXmlExtendImpl(QXmlStreamReader *root) override;
    virtual bool saveToXmlExtendImpl(QXmlStreamWriter *root) override;
    virtual void connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen) override;

private:
    static void initialStaVar();

private:
    inline static const QString __xmlLabel{"Switch"};

    inline static bool __intialSta = false;

    inline static int __switchRadius;

    inline static QSize __switchSize;
    inline static QSize __switchCenCirSizeHalf;
    inline static QSize __switchCenCirSize;

    inline static QPoint __textLBPos;
    inline static QPoint __unactCirPos;
    inline static QPoint __actCirPos;


    inline static QRect __switchRect;

    inline static QColor __switchColor;//White
    inline static QPen __switchPen;
    inline static QBrush __switchBrush;

    inline static QColor __unactSwiCenCirColor;//Gray
    inline static QPen __unactSwiCenCirPen;
    inline static QBrush __unactSwiCenCirBru;

    inline static QColor __actSwiCenCirColor;//Green
    inline static QPen __actSwiCenCirPen;
    inline static QBrush __actSwiCenCirBru;

};

#endif // SWITCHCOMPONENT_H
