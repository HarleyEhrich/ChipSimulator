#include "circuitdiagram.h"
#include "ui_circuitdiagramui.h"

CircuitDiagram::CircuitDiagram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CircuitDiagram)
{
    ui->setupUi(this);
}

CircuitDiagram::~CircuitDiagram()
{
    delete ui;
}
