#ifndef ELECSCENEVIEWCONTROLLER_H
#define ELECSCENEVIEWCONTROLLER_H

/**
*    @file:    ElecSceneViewController.h
*    @brief:   电路scene与view的管理器
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-05-18  14:50
*/

#include <QObject>
#include <QScrollArea>
#include <QFileDialog>

#include "Widgets/Graphics/AmtlGraphicsScene.h"
#include "Widgets/Graphics/AmtlGraphicsView.h"

class ElecSceneViewController : public QObject{
    Q_OBJECT

    friend class ElecPageControllor;

public:
    explicit ElecSceneViewController(QObject* parent = nullptr);
    explicit ElecSceneViewController(QString filePath , QObject* parent = nullptr);

    ~ElecSceneViewController();

public:
    QWidget* getDeaViewPage();
    QWidget* getNewViewPage(bool floatView = true);

    AmtlGraphicsSceneSPtr getScene() const;
    bool isMainViewActive();
    bool isActiveElec();

    //Quick load a new plugin
    long addANewComponnent(AbstractConInterface* factory);

    bool saveGraphicsToXMl();
    bool loadGraphicsFromXML();

private:
    void init();

    QFrame* makeSettingBox(AbstractConInterface* comptr);

    void addASettingBox(QFrame* box);

    void removeASettingBox(QFrame* box);

public:
    QString _filePath;

    AmtlGraphicsSceneSPtr _scene;
    AmtlGraphicsViewSPtr _view;

    QVBoxLayout* _scrollContentLay;
    QScrollArea* _scrollptr;
    QWidgetSPtr _sceneSetting;

    QVector<QWidget*> _floatViewBoxVec;
};
MAKE_AUTO_PTR(ElecSceneViewController);

#define SETBOX_STYLE_SHEET \
    "#box{background-color: rgb(255, 255, 255);border: 1px solid transparent;border-radius: 8px;} \
    .QScrollArea{background-color: rgb(255, 255, 255);border: 1px solid transparent;border-radius: 8px;} \
    #component_set_box{background-color: rgb(255, 255, 255);border: 1px solid transparent;border-radius: 8px;}" \

#endif // ELECSCENEVIEWCONTROLLER_H
