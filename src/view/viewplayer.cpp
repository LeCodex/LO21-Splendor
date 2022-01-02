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
        ViewToken* v = new ViewToken((Splendor::Token)i);
        viewTokens[i] = v;
        viewTokens[i]->setAmount(player->getBank().amount((Splendor::Token)i));
        QObject::connect(v, &ViewToken::tokenClicked, [v](){
            if (v->getToken() != Splendor::Gold) Splendor::QtController::getInstance().returnToken(v->getToken());
        });
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
    infoLayout->addWidget(nameLabel);
    infoLayout->addWidget(scoreLabel);
    infoLayout->addWidget(score);
    infoLayout->addWidget(handButton);

    bonusLayout = new QHBoxLayout();
    std::string paths[5] {
        ":/cards/white",
        ":/cards/blue",
        ":/cards/green",
        ":/cards/red",
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
    int amounts[5] = {0, 0, 0, 0, 0};
    for (size_t i = 0; i < 3; i++) {
        auto level = player->getRessources(i);
        for (auto c : level) {
            amounts[c->getResource()]++;
        }
    }

    for (size_t i = 0; i < 5; i++) {
        viewBonus[i]->updateAmount(amounts[i]);
    }

    // Reserved
    size_t amount = 0;
    for (size_t i = 0; i < 3; i++) {
        if (player->getReservedCard(i)) {
            ViewResourceCard* v = viewReservedCards[i];
            v->setCard(player->getReservedCard(i));

            amount++;
        }else{
            viewReservedCards[i]->setCard(nullptr);
        }
    }
    std::string text = "Montrer les cartes réservées (";
    text.append(std::to_string(amount));
    text.append(")");
    handButton->setText(text.c_str());

    // Score
    score->display(player->getScore());
}

void ViewPlayer::updateTokens() {
    for (size_t i = 0; i < 6; i ++) {
        viewTokens[i]->setAmount(player->getBank().amount((Splendor::Token)i));
    }
}

ViewPlayer::~ViewPlayer() {
    delete bankLayout;
    delete bonusLayout;
    delete infoLayout;
    delete nameLabel;
    delete scoreLabel;
    delete score;
    if(hand) delete hand;
    delete handButton;
}
