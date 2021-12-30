#ifndef VUEDRAWPILE_H
#define VUEDRAWPILE_H

#include <QWidget>
#include <QLCDNumber>
#include "../Splendor.h"
#include "viewclickable.h"
#include "../DrawPile.h"
#include <QDebug>

class ViewDrawPile : public ViewClickable
{
    Q_OBJECT
private:
    QLCDNumber* quantity;

    Splendor::DrawPile* drawPile;
    size_t index;
public:
    ViewDrawPile(Splendor::DrawPile& d, size_t index, QWidget* parent = nullptr);
    void updateQuantity();
    size_t getDrawPileIndex(){ return index; }

signals:
    void drawPileClicked(ViewDrawPile*);
public slots:
private slots:
    void clickedEvent() { emit drawPileClicked(this); }
};

#endif // VUEDRAWPILE_H
