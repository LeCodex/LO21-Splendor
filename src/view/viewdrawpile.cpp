#include "viewdrawpile.h"

ViewDrawPile::ViewDrawPile(Splendor::DrawPile& d, size_t index, QWidget* parent): ViewClickable(parent), drawPile(&d), index(index)
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
