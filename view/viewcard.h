#ifndef VUECARD_H
#define VUECARD_H

#include <QLCDNumber>
#include <QLayout>
#include "splendor.h"
#include "viewclickable.h"
#include "viewcost.h"

class ViewCard : public ViewClickable
{
    Q_OBJECT
protected:
    const Splendor::BaseCard* card = nullptr;
    QLCDNumber* number;
    ViewCost* costs[5];
    QVBoxLayout* costLayout;

    virtual void updateImage() = 0;
    virtual void updateCost();
    virtual void updatePrestige();
public:
    explicit ViewCard(QWidget* parent = nullptr);
    const Splendor::BaseCard& getCard() const { return *card; }
    void setCard(const Splendor::BaseCard* c) { card = c; updateImage(); updateCost(); updatePrestige(); }

signals:
    void cardClicked(ViewCard*);
public slots:
private slots:
    void clickedEvent() { emit cardClicked(this); }
};

#endif // VUECARD_H
