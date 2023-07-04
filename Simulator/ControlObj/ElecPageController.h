#ifndef ELECPAGECONTROLLER_H
#define ELECPAGECONTROLLER_H

#include "Pages/ElecPages/ElecPage.h"

class ElecPageController : public QObject
{
    Q_OBJECT
private:
    explicit ElecPageController(QObject *parent = nullptr){

    }
    virtual ~ElecPageController(){
    }

public:
    static ElecSceneViewControllerSPtr getCurActPage();
    static AmtlGraphicsSceneSPtr getCurActScene();
    static void removePage(ElecPage* page);

public:
    inline static QVector<ElecPage*> _elecPages;
};



#endif // ELECPAGECONTROLLER_H
