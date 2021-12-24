#include "viewcost.h"

ViewCost::ViewCost(QWidget *parent) : QWidget(parent)
{
    image = new QLabel(this);
    amount = new QLCDNumber(this);
}

ViewCost::~ViewCost() {
    delete(image);
    delete(amount);
}
