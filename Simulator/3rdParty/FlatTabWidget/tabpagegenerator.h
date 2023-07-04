#ifndef TABPAGEGENERATOR_H
#define TABPAGEGENERATOR_H

#include <QWidget>

class TabPageGenerator
{
public:
    TabPageGenerator();

public:
    virtual QWidget* page() = 0 ;
};

#endif // TABPAGEGENERATOR_H
