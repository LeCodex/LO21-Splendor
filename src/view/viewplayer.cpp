#include "viewplayer.h"
#include "../controller.h"

ViewPlayer::ViewPlayer(Splendor::Player* p, QWidget *parent) : QFrame(parent), player(p), nbReserved(0)
{
    // Score
    score = new QLCDNumber();
    score->display(0);

    // Bank
    bankLayout = new QHBoxLayout();
    for (int i = 0; i < 6; i++) {
        viewTokens[i] = new ViewToken((Splendor::Token)i);
        viewTokens[i]->setAmount(0);
        bankLayout->addWidget(viewTokens[i]);
    }

    // Cards
    reservedCardsLayout = new QVBoxLayout();
    for (size_t i = 0; i < 3; i++) {
        ViewResourceCard* v = new ViewResourceCard();
        viewReservedCards[i] = v;
        v->setCard(nullptr);

        // When clicking on a reserved card, tries to buy it
        QObject::connect(v, &ViewResourceCard::cardClicked, [this, v](){
            if(v->getCard())
                if(Splendor::QtController::getInstance().buyReservedCard((Splendor::ResourceCard*) v->getCard()))
                    this->hand->hide();
        });

        reservedCardsLayout->addWidget(viewReservedCards[i]);
    }

    // Hand
    hand = new QWidget();
    hand->setLayout(reservedCardsLayout);

    handButton = new QPushButton();
    handButton->setText("Montrer les cartes réservées (0)");
    connect(handButton, SIGNAL(clicked()), this, SLOT(showHand()));

    // Infos
    scoreLabel = new QLabel();
    scoreLabel->setText("Score:");
//    scoreLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    nameLabel = new QLabel();
    nameLabel->setText(player->getName().c_str());

    infoLayout = new QHBoxLayout();
    infoLayout->addWidget(scoreLabel);
    infoLayout->addWidget(score);
    infoLayout->addWidget(handButton);

    bonusLayout = new QHBoxLayout();
    std::string paths[5] {
        ":/cards/red",
        ":/cards/blue",
        ":/cards/green",
        ":/cards/white",
        ":/cards/black"
    };
    for (size_t i = 0; i < 5; i++) {
        viewBonus[i] = new ViewBonus(paths[i]);
        bonusLayout->addWidget(viewBonus[i]);
    }

    layer = new QVBoxLayout();
    layer->addLayout(infoLayout);
    layer->addLayout(bonusLayout);
    layer->addLayout(bankLayout);

    setLayout(layer);
    setFrameStyle(1);

    setAsCurrent(false);
}

void ViewPlayer::updateCurrentStatus() {
    handButton->setDisabled(!isCurrent);
    for (size_t i = 0; i < 5; i ++) viewBonus[i]->setDisabled(!isCurrent);
    for (size_t i = 0; i < 6; i ++) viewTokens[i]->setDisabled(!isCurrent);
    setFrameShadow(isCurrent ? Shadow::Raised : Shadow::Plain);
};

void ViewPlayer::updateCards() {
    // Resources
    std::vector<const Splendor::ResourceCard*> cards;
    for (size_t i = 0; i < 3; i++) {
        auto level = player->getRessources(i);
        for (auto c : level) {
            cards.push_back(c);
        }
    }

    int amounts[5] = {0, 0, 0, 0, 0};
    for (auto c : cards) {
        amounts[c->getResource()]++;
    }

    for (size_t i = 0; i < 5; i++) {
        viewBonus[i]->updateAmount(amounts[i]);
    }

    // Reserved
    size_t amount = 0;
    for (size_t i = 0; i < 3; i++) {
        if (player->getReservedCards(i)) {
            ViewResourceCard* v = viewReservedCards[i];
            v->setCard(player->getReservedCards(i));

            amount++;
        }else{
            viewReservedCards[i]->setCard(nullptr);
        }
    }
    std::string text = "Montrer les cartes réservées (";
    text.append(std::to_string(amount));
    text.append(")");
    handButton->setText(text.c_str());
}

void ViewPlayer::updateTokens() {
    for (size_t i = 0; i < 6; i++) {
        viewTokens[i]->setAmount(player->getBank().getAll()[i]);
    }
}

ViewPlayer::~ViewPlayer() {
    delete(bankLayout);
    delete(bonusLayout);
    delete(infoLayout);
    delete(nameLabel);
    delete(scoreLabel);
    delete(score);
    delete(hand);
    delete(handButton);
}
