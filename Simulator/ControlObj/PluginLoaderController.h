#ifndef PLUGINLOADERCONTROLLER_H
#define PLUGINLOADERCONTROLLER_H

/**
*    @file:    PluginLoaderController.h
*    @brief: 组件加载器--生成了组件UI
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-05-18  14:50
*/


#include <QDir>
#include <QJsonObject>
#include <QMultiMap>
#include <QObject>
#include <QPluginLoader>
#include <QUrl>

#include <abstractconinterface.h>

#include "Widgets/UiItemWidgets/ComponentWidget.h"

#define WRITE_PTR(ptr,msg) if(nullptr != ptr){(*ptr) = msg;}
#define NO_CATEGORY "NO_CATE"

class PluginLoaderController : public QObject
{
    Q_OBJECT
private:
    explicit PluginLoaderController(QObject *parent = nullptr);

signals:
    void pluginLoadDone(const QStringList& componentNameList);

private slots:

public:
    void scanPluginFolder(bool manualInputPath = false,QString path = "");

    AbstractConInterface* getComById(const QString comId);

    QJsonObject getJsonByComId(const QString comId);

    QJsonObject getMetaDataJsonObjByComId(const QString comId);

    QString getComCategory(const QString comId);

    QStringList comNameList() const;

    QStringList comIdList() const;

    QVector<ComponentUiItemWidgetSPtr> getComponentAllItemWidgets();


private:
    void init();
    void scanPluginFolderImpl(const QString& path);
    bool loadAPlugin(const QString& pluginPath, QString* loadMsg = nullptr);

private:
    QStringList _comNameList;//Comname+author+creat time
    QStringList _comIdList;//ComId list
    QVector<ComponentFullInfoStruct> _comFullInfoStructVec;//存储组件所对应的信息，包含类别等
    QVector<ComponentUiItemWidgetSPtr> _comSelectUiWidget;//存储对应的ui实例

    QMap<QString,QJsonObject> _idJsonMap;
    QMap<QString,AbstractConInterface*> _idComponentMap;
    QMultiMap<QString,AbstractConInterface*> _cateConponentMMap;

public:
    static PluginLoaderController* instance();
};

#endif // PLUGINLOADERCONTROLLER_H
