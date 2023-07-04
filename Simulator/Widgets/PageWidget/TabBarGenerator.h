#ifndef TABBARGENERATOR_H
#define TABBARGENERATOR_H

#include <QWidget>

class TabPageGenerator
{
public:
    TabPageGenerator();

public:
    virtual QWidget* page() = 0 ;
};

#endif // TABBARGENERATOR_H
