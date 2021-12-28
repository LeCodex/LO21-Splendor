#include "viewcost.h"

ViewCost::ViewCost(QWidget *parent) : QWidget(parent)
{
    amount = new QLCDNumber(1, this);
    amount->setFrameStyle(0);
    amount->setContentsMargins(0, 0, 0, 0);
    amount->setMinimumHeight(50);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ViewCost::~ViewCost() {
    delete(amount);
}
