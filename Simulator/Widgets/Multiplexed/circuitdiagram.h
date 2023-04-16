#ifndef CIRCUITDIAGRAM_H
#define CIRCUITDIAGRAM_H

/**
*    @file:    circuitdiagram.h
*    @brief:   再次出完成对组件的申请，--没用这玩意目前
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-04-13  17:32
*/


#include <QWidget>

namespace Ui {
class CircuitDiagram;
}

class CircuitDiagram : public QWidget
{
    Q_OBJECT

public:
    explicit CircuitDiagram(QWidget *parent = nullptr);
    ~CircuitDiagram();

private:
    Ui::CircuitDiagram *ui;
};

#endif // CIRCUITDIAGRAM_H
