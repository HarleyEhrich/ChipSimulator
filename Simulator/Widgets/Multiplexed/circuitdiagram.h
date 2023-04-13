#ifndef CIRCUITDIAGRAM_H
#define CIRCUITDIAGRAM_H

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
