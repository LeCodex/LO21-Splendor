#ifndef VUEBOARD_H
#define VUEBOARD_H

#include <QWidget>
#include <QLayout>
#include "vueresourcecard.h"
#include "vuenoblecard.h"
#include "vuetoken.h"

class VueBoard : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* resourceCardsLayout;
    QVBoxLayout* centralBankLayout;
    QHBoxLayout* nobleCardsLayout;
    std::vector<VueResourceCard*> vueResourceCards;
    std::vector<VueNobleCard*> vueNobleCards;
    VueToken* vueTokens[6]; // The bank
public:
    explicit VueBoard(QWidget *parent = nullptr);

signals:

};

#endif // VUEBOARD_H
