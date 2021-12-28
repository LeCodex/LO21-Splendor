#include "viewcard.h"

ViewCard::ViewCard(QWidget* parent) : ViewClickable(parent), card(nullptr)
{
    number = new QLCDNumber();
    number->setFrameStyle(0);
    number->setMinimumHeight(50);
    number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    costLayout = new QVBoxLayout();
    costLayout->setContentsMargins(5, 0, 0, 20);
    for (size_t i = 0; i < 5; i ++) {
        costs[i] = new ViewCost();
        costLayout->addWidget(costs[i]);
    }

    rightLayout = new QVBoxLayout();
    rightLayout->addWidget(number);

    layer = new QHBoxLayout();
    layer->addLayout(costLayout);
    layer->addLayout(rightLayout);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setLayout(layer);
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
