#ifndef VUEPLAYER_H
#define VUEPLAYER_H

#include <QWidget>
#include <QLayout>
#include "vuetoken.h"
#include "vueresourcecard.h"
#include "vuenoblecard.h"

class VuePlayer : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* bankLayout;
    QVBoxLayout* reservedCardsLayout;
    QVBoxLayout* resourcesLayout[3];
    QVBoxLayout* noblesLayout;
    QHBoxLayout* cardsLayout;
    QVBoxLayout* globalLayout;
    VueToken* vueTokens[6];
    std::vector<VueResourceCard*> vueResourceCards;
    std::vector<VueNobleCard*> vueNobleCards;
public:
    explicit VuePlayer(QWidget *parent = nullptr);
    VueToken* getToken(Splendor::Token token) const { return vueTokens[token]; }
    std::vector<VueResourceCard*> getResources() const { return vueResourceCards; }
    std::vector<VueNobleCard*> getNobles() const { return vueNobleCards; }

signals:

};

#endif // VUEPLAYER_H
