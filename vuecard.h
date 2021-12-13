#ifndef VUECARD_H
#define VUECARD_H

#include <QPushButton>
#include "splendor.h"

class VueCard : public QPushButton
{
    Q_OBJECT
protected:
    const Splendor::BaseCard* card = nullptr;
public:
    explicit VueCard(const Splendor::BaseCard* c, QWidget* parent = nullptr);
    const Splendor::BaseCard& getCard() const { return *card; }

signals:
    void carteClicked(VueCard*);
public slots:
private slots:
    void clickedEvent() { emit carteClicked(this); }
};

#endif // VUECARD_H
