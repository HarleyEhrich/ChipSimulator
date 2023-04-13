#ifndef CONLINKLINE_H
#define CONLINKLINE_H

#include <QGenericPlugin>

class ConLinkLine : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGenericPluginFactoryInterface_iid FILE "BasicCon.json")

public:
    explicit ConLinkLine(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // CONLINKLINE_H
