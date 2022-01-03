#ifndef VUEPLAYER_H
#define VUEPLAYER_H

#include <QWidget>
#include <QLayout>
#include "viewtoken.h"
#include "viewbonus.h"
#include "viewresourcecard.h"
#include "viewnoblecard.h"
#include "../Player.h"
#include "../ResourceCard.h"
#include "../NobleCard.h"
#include <initializer_list>
#include <list>

class ViewPlayer : public QFrame
{
    Q_OBJECT
private:
    Splendor::Player* player;

    QHBoxLayout* infoLayout;
    QLCDNumber* score;
    QLabel* scoreLabel;
    QLabel* nameLabel;
    QLabel* noblesLabel;

    ViewResourceCard* viewReservedCards[3];
    QVBoxLayout* reservedCardsLayout;
    size_t nbReserved = 0;
    QPushButton* handButton;
    QWidget* hand;

    QHBoxLayout* bonusLayout;
    ViewBonus* viewBonus[6];

    QHBoxLayout* bankLayout;
    ViewToken* viewTokens[6];

    QVBoxLayout* layer;

    bool isCurrent;

    void updateCurrentStatus();
public:
    explicit ViewPlayer(Splendor::Player* player, QWidget *parent = nullptr);
    ViewToken* getToken(Splendor::Token token) const { return viewTokens[token]; }

    void setAsCurrent(bool c) { isCurrent = c; updateCurrentStatus(); } // Pour marquer pour quel joueur c'est le tour
    auto getHand() const{ return hand; }
    auto getReservedCards() const { return viewReservedCards; }
    auto getTokens() const { return viewTokens; }
    auto getBonus() const { return viewBonus; }

    void updateCards();
    void updateTokens();

    ~ViewPlayer();

private slots:
    void showHand() { hand->show(); }
};

#endif // VUEPLAYER_H
