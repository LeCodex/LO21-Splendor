#include "viewboard.h"

ViewBoard::ViewBoard(Splendor::Board& b, QWidget *parent) : QWidget(parent), board(&b)
{
    // Central bank
    centralBankLayout = new QVBoxLayout();
    for (size_t i = 0; i < 6; i++) {
        viewTokens[i] = new ViewToken((Splendor::Token)i);
        viewTokens[i]->setAmount(8);
        centralBankLayout->addWidget(viewTokens[i]);
    }

    // Noble cards
    nobleCardsLayout = new QHBoxLayout();

    // Resource cards
    resourceCardsLayout = new QGridLayout();
    for (size_t i = 0; i < 3; i++) {
        viewDrawPiles.push_back(new ViewDrawPile(board->getDrawPile(i)));
        resourceCardsLayout->addWidget(viewDrawPiles.back(), i, 0);
        for (size_t j = 0; j < 4; j ++) {
            viewResourceCards.push_back(new ViewResourceCard());
            viewResourceCards.back()->setCard(nullptr);
            resourceCardsLayout->addWidget(viewResourceCards.back(), i, j + 1);
        }
    }

    cardBoardLayout = new QVBoxLayout();
    cardBoardLayout->addLayout(nobleCardsLayout, 1);
    cardBoardLayout->addLayout(resourceCardsLayout, 9);

    layer = new QHBoxLayout();
    layer->addLayout(centralBankLayout);
    layer->addLayout(cardBoardLayout);

    setLayout(layer);

    updateCards();
    updateTokens();
}

void ViewBoard::updateCards() {
    // Nobles
    for (size_t i = 0; i < viewNobleCards.size(); i++) {
        delete(viewNobleCards[i]);
    }

    auto nobles = board->getNobles();
    for (size_t i = 0; i < nobles.size(); i++) {
        viewNobleCards.push_back(new ViewNobleCard());
        viewNobleCards.back()->setCard(nobles[i]);
        nobleCardsLayout->addWidget(viewNobleCards.back());
    }

    // Resources
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j ++) {
           viewResourceCards[j + i * 4]->setCard(&board->getCard(i, j));
        }
    }
}

void ViewBoard::updateTokens() {
    for (size_t i = 0; i < 6; i ++) {
        viewTokens[i]->setAmount(board->getBank().getAll()[i]);
    }
}
