#include "viewcost.h"

ViewCost::ViewCost(QWidget *parent) : QWidget(parent)
{
    amount = new QLCDNumber(1, this);
    amount->setFixedHeight(50);
    amount->setFixedWidth(20);
    amount->setFrameStyle(0);
    amount->setContentsMargins(0, 0, 0, 0);

    setFixedHeight(50);
    setFixedWidth(20);
}

ViewCost::~ViewCost() {
    delete(amount);
}
