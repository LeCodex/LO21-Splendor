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
    QGridLayout* resourceCardsLayout;
    QVBoxLayout* centralBankLayout;
    QHBoxLayout* nobleCardsLayout;
    std::vector<ViewResourceCard*> viewResourceCards;
    std::vector<ViewNobleCard*> viewNobleCards;
    ViewToken* viewTokens[6]; // The bank

    Splendor::Board* board;
public:
    explicit ViewBoard(Splendor::Board& b, QWidget *parent = nullptr);

signals:

};

#endif // VUEBOARD_H
