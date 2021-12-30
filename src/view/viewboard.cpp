#include "viewboard.h"
#include "../controller.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

ViewBoard::ViewBoard(Splendor::Board& b, QWidget *parent) : QWidget(parent), board(&b)
{
    // Central bank
    centralBankLayout = new QVBoxLayout();
    for (size_t i = 0; i < 6; i++) {
        ViewToken* v = new ViewToken((Splendor::Token)i);
        viewTokens[i] = v;
        viewTokens[i]->setAmount(board->getBank().amount((Splendor::Token)i));
        QObject::connect(v, &ViewToken::tokenClicked, [v](){
            QDialog dialog;

            dialog.setWindowTitle("Splendor");

            QVBoxLayout vBox;
            QLabel label("Que voulez vous faire?");
            vBox.addWidget(&label);

            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
            QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

            buttonBox.button(QDialogButtonBox::Ok)->setText("Prendre 2 tokens identiques");
            buttonBox.button(QDialogButtonBox::Ok)->setIcon(QIcon());

            buttonBox.button(QDialogButtonBox::Cancel)->setText("Prendre 3 tokens différents");
            buttonBox.button(QDialogButtonBox::Cancel)->setIcon(QIcon());

            vBox.addWidget(&buttonBox);

            dialog.setLayout(&vBox);

            // Execute the action
            if(dialog.exec() == QDialog::Accepted) Splendor::QtController::getInstance().takeTwoIdenticalToken(v->getToken());
            // else Splendor::QtController::getInstance().takeThreeDifferentToken();

        });
        centralBankLayout->addWidget(viewTokens[i]);
    }

    // Noble cards
    nobleCardsLayout = new QHBoxLayout();

    // Resource cards
    resourceCardsLayout = new QGridLayout();
    for (size_t i = 0; i < 3; i++) {
        viewDrawPiles.push_back(new ViewDrawPile(board->getDrawPile(i),i));

        // When clicking on a drawpile, tries to reserve
        QObject::connect(viewDrawPiles.back(), &ViewDrawPile::drawPileClicked, [i](){
            Splendor::QtController::getInstance().reserveDrawCard(i);
        });

        resourceCardsLayout->addWidget(viewDrawPiles.back(), i, 0);
        for (size_t j = 0; j < 4; j ++) {
            ViewResourceCard *v = new ViewResourceCard();
            viewResourceCards.push_back(v);
            v->setCard(nullptr);

            // When clicking on a card, try to reserve or buy it
            QObject::connect(v, &ViewResourceCard::cardClicked, [v](){
                QDialog dialog;

                dialog.setWindowTitle("Splendor");

                QVBoxLayout vBox;
                QLabel label("Que voulez vous faire?");
                vBox.addWidget(&label);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
                QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
                QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

                buttonBox.button(QDialogButtonBox::Ok)->setText("Acheter la carte");
                buttonBox.button(QDialogButtonBox::Ok)->setIcon(QIcon());

                buttonBox.button(QDialogButtonBox::Cancel)->setText("Reserver la carte");
                buttonBox.button(QDialogButtonBox::Cancel)->setIcon(QIcon());

                vBox.addWidget(&buttonBox);

                dialog.setLayout(&vBox);

                // Execute the action
                if(dialog.exec() == QDialog::Accepted) Splendor::QtController::getInstance().buyBoardCard((Splendor::ResourceCard*) v->getCard());
                else Splendor::QtController::getInstance().reserveCenterCard((Splendor::ResourceCard*) v->getCard());

            });

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

    viewNobleCards.clear();

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

    // DrawPiles
    for (size_t i = 0; i < 3; i++)
        viewDrawPiles[i]->updateQuantity();
}

void ViewBoard::updateTokens() {
    for (size_t i = 0; i < 6; i ++) {
        viewTokens[i]->setAmount(board->getBank().amount((Splendor::Token)i));
    }
}

ViewBoard::~ViewBoard() {
    delete centralBankLayout;
    delete nobleCardsLayout;
    delete resourceCardsLayout;
    delete cardBoardLayout;
    delete layer;
}
