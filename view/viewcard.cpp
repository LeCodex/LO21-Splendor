#include "viewcard.h"

ViewCard::ViewCard(QWidget* parent) : ViewClickable(parent), card(nullptr)
{
    setFixedWidth(150);
    setFixedHeight(200);

    number = new QLCDNumber(this);
    number->setGeometry(0, 0, 150, 50);
    number->setFrameStyle(0);

    costLayout = new QVBoxLayout();
    costLayout->setContentsMargins(5, 0, 0, 20);

    for (size_t i = 0; i < 5; i ++) {
        costs[i] = new ViewCost();
        costLayout->addWidget(costs[i]);
    }

    setLayout(costLayout);
}

void ViewCard::updatePrestige() {
    if (!card) {
        number->hide();
    } else {
        number->display(card->getPrestige());
        if (card->getPrestige() == 0) number->hide(); else number->show();
    }
}

void ViewCard::updateCost() {
    // Hide
    for (auto i: costs) {
        i->getAmount()->hide();
    }

    if (!card) {
        return;
    } else {
        Qt::GlobalColor colors[5] {
            Qt::red,
            Qt::blue,
            Qt::green,
            Qt::white,
            Qt::black
        };

        size_t j = 0;
        for (size_t i = 0; i < 5; i ++) {
            int c = card->getTokenCost((Splendor::Token)i);

            if (c > 0) {
                costs[j]->getAmount()->display(c);
                costs[j]->getAmount()->setPalette(colors[i]);
                costs[j]->getAmount()->show();
                j++;
            }
        }
    }
}
