#include "DevAssistance.h"

std::shared_ptr<DevelopmentAssistance> DevelopmentAssistance::__assistSharedPtr{new DevelopmentAssistance{}};

DevelopmentAssistance::DevelopmentAssistance(QObject *parent)
    : QObject{parent}
{

}
