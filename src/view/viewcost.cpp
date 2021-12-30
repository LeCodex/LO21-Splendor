#include "viewcost.h"

ViewCost::ViewCost(QWidget *parent) : QWidget(parent)
{
    amount = new QLCDNumber(1, this);
    amount->setFrameStyle(0);
    amount->setContentsMargins(0, 0, 0, 0);

    setContentsMargins(0, 0, 0, 0);
//    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

ViewCost::~ViewCost() {
    delete amount;
}
