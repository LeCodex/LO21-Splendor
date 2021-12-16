#ifndef VUEPLAYER_H
#define VUEPLAYER_H

#include <QWidget>
#include <QLayout>
#include "viewtoken.h"
#include "viewresourcecard.h"
#include "viewnoblecard.h"

class ViewPlayer : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* bankLayout;
    QVBoxLayout* reservedCardsLayout;
    QVBoxLayout* resourcesLayout[3];
    QVBoxLayout* noblesLayout;
    QHBoxLayout* cardsLayout;
    QVBoxLayout* globalLayout;
    ViewToken* viewTokens[6];
    std::vector<ViewResourceCard*> viewResourceCards;
    std::vector<ViewNobleCard*> viewNobleCards;
public:
    explicit ViewPlayer(QWidget *parent = nullptr);
    ViewToken* getToken(Splendor::Token token) const { return viewTokens[token]; }
    std::vector<ViewResourceCard*> getResources() const { return viewResourceCards; }
    std::vector<ViewNobleCard*> getNobles() const { return viewNobleCards; }

signals:
};

#endif // VUEPLAYER_H
