#ifndef VUEPLAYER_H
#define VUEPLAYER_H

#include <QWidget>
#include <QLayout>
#include "viewtoken.h"
#include "viewbonus.h"
#include "viewresourcecard.h"
#include "viewnoblecard.h"
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

    std::vector<ViewResourceCard*> viewResourceCards;
    std::vector<ViewNobleCard*> viewNobleCards;

    bool isCurrent;

    void updateCurrentStatus();
public:
    explicit ViewPlayer(Splendor::Player* player, QWidget *parent = nullptr);
    ViewToken* getToken(Splendor::Token token) const { return viewTokens[token]; }
    std::vector<ViewResourceCard*> getResources() const { return viewResourceCards; }
    std::vector<ViewNobleCard*> getNobles() const { return viewNobleCards; }

    void setAsCurrent(bool c) { isCurrent = c; updateCurrentStatus(); } // Pour marquer pour quel joueur c'est le tour
    auto getResourceCards() const { return viewResourceCards; }
    auto getReservedCards() const { return viewReservedCards; }
    auto getNobleCards() const { return viewNobleCards; }
    auto getTokens() const { return viewTokens; }
    auto getBonus() const { return viewBonus; }

    void updateCards();
    void updateTokens();

    ~ViewPlayer();

private slots:
    void showHand() { hand->show(); }
};

#endif // VUEPLAYER_H
