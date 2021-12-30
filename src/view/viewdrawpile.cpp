#include "viewdrawpile.h"

ViewDrawPile::ViewDrawPile(Splendor::DrawPile& d, QWidget* parent): ViewClickable(parent), drawPile(&d)
{
    quantity = new QLCDNumber(this);
    quantity->setFrameStyle(0);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    updateQuantity();
}

void ViewDrawPile::updateQuantity() {
    quantity->display((int)drawPile->getCardAmount());
    quantity->setPalette(Qt::darkGray);

    if (drawPile->getCardAmount() == 0)
        quantity->setPalette(Qt::red);
}

ViewDrawPile::~ViewDrawPile() {
    delete quantity;
}
