#ifndef VUEBOARD_H
#define VUEBOARD_H

#include <QWidget>
#include <QLayout>
#include "viewresourcecard.h"
#include "viewnoblecard.h"
#include "viewtoken.h"

class ViewBoard : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* layer;
    QVBoxLayout* cardBoardLayout;
    QGridLayout* resourceCardsLayout;
    QVBoxLayout* centralBankLayout;
    QHBoxLayout* nobleCardsLayout;
    std::vector<ViewResourceCard*> viewResourceCards;
    std::vector<ViewNobleCard*> viewNobleCards;
    ViewToken* viewTokens[6]; // The bank

    Splendor::Board* board;
public:
    explicit ViewBoard(Splendor::Board& b, QWidget *parent = nullptr);

    auto getResourceCards() const { return viewResourceCards; }
    auto getNobleCards() const { return viewNobleCards; }
    auto getTokens() const { return viewTokens; }

    void updateCards();
    void updateTokens();

signals:

};

#endif // VUEBOARD_H
