#include "viewcard.h"

ViewCard::ViewCard(QWidget* parent) : ViewClickable(parent), card(nullptr)
{
    number = new QLCDNumber();
    number->setFrameStyle(0);
    number->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    costLayout = new QVBoxLayout();
    costLayout->setDirection(QBoxLayout::Direction::TopToBottom);
    costLayout->setContentsMargins(0, 0, 0, 0);
    costLayout->setSpacing(0);
    for (size_t i = 0; i < 5; i ++) {
        costs[i] = new ViewCost();
        costLayout->addWidget(costs[i]);
    }

    rightLayout = new QVBoxLayout();
    rightLayout->addWidget(number);

    layer = new QHBoxLayout();
    layer->setDirection(QBoxLayout::Direction::LeftToRight);
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
            int c = card->getCost((Splendor::Token)i);

            // qInfo() << QString::fromStdString(Splendor::getTokenName((Splendor::Token) i)) << " : " << c << "\n";

            if (c > 0) {

                costs[j]->getAmount()->display(c);
                costs[j]->getAmount()->setPalette(colors[i]);
                costs[j]->getAmount()->show();
                j++;
            }
        }
    }
}

ViewCard::~ViewCard() {
    delete number;
    delete costLayout;
    delete rightLayout;
    delete layer;
    for (size_t i = 1; i < 5; i++) if (costs[i]) delete costs[i];
}
