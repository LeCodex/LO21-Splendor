#ifndef VUEBOARD_H
#define VUEBOARD_H

#include <QWidget>
#include <QLayout>
#include "viewresourcecard.h"
#include "viewnoblecard.h"
#include "viewtoken.h"
#include "viewdrawpile.h"
#include "../board.h"

class ViewBoard : public QWidget
{
    Q_OBJECT
private:
    Splendor::Board* board;
protected:
    virtual void createBank();
    virtual void createNobles();
    virtual void createResources();

    QHBoxLayout* layer;
    QVBoxLayout* cardBoardLayout;
    QGridLayout* resourceCardsLayout;
    QVBoxLayout* centralBankLayout;
    QHBoxLayout* nobleCardsLayout;
    std::vector<ViewResourceCard*> viewResourceCards;
    std::vector<ViewNobleCard*> viewNobleCards;
    std::vector<ViewDrawPile*> viewDrawPiles;
    ViewToken* viewTokens[6]; // The bank
public:
    explicit ViewBoard(Splendor::Board& b, QWidget *parent = nullptr);

    auto getResourceCards() const { return viewResourceCards; }
    auto getNobleCards() const { return viewNobleCards; }
    auto getTokens() const { return viewTokens; }

    void updateCards();
    void updateTokens();

    virtual ~ViewBoard();

signals:

};

#endif // VUEBOARD_H
