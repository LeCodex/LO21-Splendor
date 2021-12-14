#ifndef VUECARD_H
#define VUECARD_H

#include <QPushButton>
#include <QLCDNumber>
#include "splendor.h"
#include "vueclickable.h"

class VueCard : public VueClickable
{
    Q_OBJECT
protected:
    const Splendor::BaseCard* card = nullptr;
    bool hidden = false;

    QImage background;
    QImage back;
    QLCDNumber prestigeNumber;
public:
    explicit VueCard(const Splendor::BaseCard* c, QWidget* parent = nullptr);
    const Splendor::BaseCard& getCard() const { return *card; }
    void setHidden(bool h) { hidden = h; }
    bool getHidden() const { return hidden; }

signals:
    void cardClicked(VueCard*);
public slots:
private slots:
    void clickedEvent() { emit cardClicked(this); }
};

#endif // VUECARD_H
