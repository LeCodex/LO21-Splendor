#ifndef VUECARD_H
#define VUECARD_H

#include <QLCDNumber>
#include "splendor.h"
#include "viewclickable.h"

class ViewCard : public ViewClickable
{
    Q_OBJECT
protected:
    const Splendor::BaseCard* card = nullptr;

    QImage background;
    QImage back;
    QLCDNumber prestigeNumber;
public:
    explicit ViewCard(const Splendor::BaseCard* c, QWidget* parent = nullptr);
    const Splendor::BaseCard& getCard() const { return *card; }

signals:
    void cardClicked(ViewCard*);
public slots:
private slots:
    void clickedEvent() { emit cardClicked(this); }
};

#endif // VUECARD_H
