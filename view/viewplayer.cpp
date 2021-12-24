#include "viewplayer.h"

ViewPlayer::ViewPlayer(QWidget *parent) : QWidget(parent)
{
    // Bank
    bankLayout = new QHBoxLayout();
    for (int i = 0; i < 6; i++) {
        viewTokens[i] = new ViewToken((Splendor::Token)i);
        viewTokens[i]->setAmount(8);
        bankLayout->addWidget(viewTokens[i]);
    }

    // Cards
    noblesLayout = new QVBoxLayout();
    reservedCardsLayout = new QVBoxLayout();

    cardsLayout = new QHBoxLayout();
    cardsLayout->addLayout(noblesLayout);
    for (auto r : resourcesLayout) cardsLayout->addLayout(r);
    cardsLayout->addLayout(reservedCardsLayout);

    layer = new QVBoxLayout();
    layer->addLayout(bankLayout);
    layer->addLayout(cardsLayout);

    setLayout(layer);
}
