#include "viewboard.h"

ViewBoard::ViewBoard(Splendor::Board& b, QWidget *parent) : QWidget(parent), board(&b)
{
    // Central bank
    centralBankLayout = new QVBoxLayout();
    for (int i = 0; i < 6; i++) {
        viewTokens[i] = new ViewToken((Splendor::Token)i);
        viewTokens[i]->setAmount(8);
        centralBankLayout->addWidget(viewTokens[i]);
    }

    // Noble cards
    nobleCardsLayout = new QHBoxLayout();
    for (int i = 0; i < 5; i++) {
        viewNobleCards.push_back(new ViewNobleCard());
        viewNobleCards.back()->setCard(nullptr);
        nobleCardsLayout->addWidget(viewNobleCards.back());
    }

    // Resource cards
    resourceCardsLayout = new QGridLayout();

    cardBoardLayout = new QVBoxLayout();
    cardBoardLayout->addLayout(nobleCardsLayout);
    cardBoardLayout->addLayout(resourceCardsLayout);

    layer = new QHBoxLayout();
    layer->addLayout(centralBankLayout);
    layer->addLayout(cardBoardLayout);

    setLayout(layer);
}
