#include "viewcard.h"

ViewCard::ViewCard(QWidget* parent) : ViewClickable(parent), card(nullptr)
{
    setFixedWidth(150);
    setFixedHeight(200);

    number = new QLCDNumber(this);
    number->setGeometry(0, 0, 150, 50);
    number->setFrameStyle(0);

    for (size_t i = 0; i < 5; i ++) costs[i] = new ViewCost();
}

void ViewCard::updatePrestige() {
    if (!card) {
        number->hide();
    } else {
        number->display(card->getPrestige());
        if (card->getPrestige() == 0) number->hide(); else number->show();
    }
}
