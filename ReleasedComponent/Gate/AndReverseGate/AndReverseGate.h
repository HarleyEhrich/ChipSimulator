#ifndef ANDREVERSEGATE_H
#define ANDREVERSEGATE_H

#include <QBrush>
#include <QPen>
#include <QSize>

#include <GlobalInclude.h>
#include <abstractconinterface.h>

class AndReverseGate : public AbstractConInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID AbstractConInterface_iid FILE "AndReverseGate.json")
    Q_INTERFACES(AbstractConInterface)
public:
    explicit AndReverseGate();
    explicit AndReverseGate(long sceneID, QGraphicsItem *parent = nullptr, QObject* parentObject=nullptr);

    // AbstractConInterface interface
public slots:
    virtual void run() override;


public:
    QFont font() const;

private:
    void init();

    void runImpl();

    void updateStatus();

    void gneratePos();

    void gnerateItemPainterPathImpl();

private:
    QString _gateName;
    QPoint _gateNamePos;
    QFont _font;

    UniConnectionPointPtr _input1,_input2,_output;

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
    static void IntialStaticVariable();

private:
    inline static const QString __xmlLabel{"AndReverseGate"};
    inline static bool __intialSta = false;

    inline static QSize __mainBodySize;
    inline static QSize __mainBodySizeHalf;

    inline static QSize __reverseFlagSize;
    inline static QSize __reverseFlagSizeHalf;

    inline static QPoint __textLBPos;

    inline static QColor __mainBodyColor;
    inline static QPen __mainBodyPen;
    inline static QBrush __mainBodyBrush;

};


#endif // ANDREVERSEGATE_H
