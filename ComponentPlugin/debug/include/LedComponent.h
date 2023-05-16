#ifndef LEDCOMPONENT_H
#define LEDCOMPONENT_H

#include <QBrush>
#include <QPen>
#include <QSize>
#include <QSpinBox>

#include <GlobalInclude.h>
#include <abstractconinterface.h>

class LedComponent : public AbstractConInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AbstractConInterface_iid FILE "Led.json")
    Q_INTERFACES(AbstractConInterface)

public:
    explicit LedComponent();
    explicit LedComponent(long sceneID, QGraphicsItem *parent = nullptr, QObject* parentObject=nullptr);

signals:
    void tellLedLightBallCountChange(int newCount);

    // AbstractConInterface interface
public slots:
    virtual void run() override;

public:
    int lightBallCount() const;

    void setLightBallCount(int newLedCount);

    void updateAllStauts();

private:
    void initial();

    void setLightBallCountImpl(int newLedCount);

    bool addLightBallImpl();

    bool deleteLightBallImpl();

    void cacheData(int index = -1);

    void generatePosImpl();

    void generateItemPainterPathImpl();

    void drawALightBall(QPainter* painter,int indexOfLightBall);


private:
    int _lightBallCount;

    QPoint _textLBPos;//昵称的位置

    /// \brief 二极管左上角的位置
    QVector<QPoint> _lightBallCenterPosVec;
    //
    QVector<bool> _dataCache;//数据缓存

    QSharedPointer<QSpinBox> _ledCountSetWidget;//


public:
    // QGraphicsItem interface
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual AbstractConInterface *instanceImpl(long sceneID, QGraphicsItem *parent) override;
    virtual void gnerateItemPainterPath() override;
    virtual bool loadFromXmlExtendImpl(QXmlStreamReader *root) override;
    virtual bool saveToXmlExtendImpl(QXmlStreamWriter *root) override;
    virtual void connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen) override;


private:
    static void InitialStaticVar();

private:
    inline static const QString __LedXmlLabel{"Led"};

    inline static bool __initialStaVar = false;
    inline static int __colorLighter;
    inline static int __lightBallSperateSpace;
    inline static QSize __lightBallSizeHalf;
    inline static QSize __lightBallSize;
    inline static QSize __lightBallBaseSizeHalf;
    inline static QSize __lightBallBaseSize;

    inline static QColor __unActColor;
    inline static QPen __unActBasePen;
    inline static QBrush __unActBaseBrush;
    inline static QPen __unActPen;
    inline static QBrush __unActBrush;

    inline static QColor __actColor;
    inline static QPen __actBasePen;
    inline static QBrush __actBaseBrush;
    inline static QPen __actPen;
    inline static QBrush __actBrush;

};

#endif // LEDCOMPONENT_H
