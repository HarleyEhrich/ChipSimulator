#include "ElecPageController.h"

ElecSceneViewControllerSPtr ElecPageController::getCurActPage(){
    for(auto& elecPage : _elecPages){
        if(elecPage->_elecViewSceneControllerSPtr.isNull()){
            continue;
        }
        if(true == elecPage->_elecViewSceneControllerSPtr->isActiveElec()){
            return elecPage->_elecViewSceneControllerSPtr;
        }
    }
    return ElecSceneViewControllerSPtr{};
}

AmtlGraphicsSceneSPtr ElecPageController::getCurActScene(){
    for(auto& elcePage : _elecPages){
        if(elcePage->_elecViewSceneControllerSPtr.isNull()){
            continue;
        }

        if(true == elcePage->_elecViewSceneControllerSPtr->isMainViewActive()){
            return elcePage->_elecViewSceneControllerSPtr->getScene();
        }
    }
    return AmtlGraphicsSceneSPtr{};
}

void ElecPageController::removePage(ElecPage *page){
    QVector<ElecPage*>::const_iterator iter = _elecPages.constBegin();
    while(iter!=_elecPages.end()){
        if(*iter == page){
            _elecPages.erase(iter);
            break;
        }
        iter++;
    }
}
