#ifndef VUEDRAWPILE_H
#define VUEDRAWPILE_H

#include <QWidget>
#include "../Splendor.h"
#include "viewclickable.h"
#include "../DrawPile.h"

class ViewDrawPile : public ViewClickable
{
    Q_OBJECT
private:
    QImage back;

    Splendor::DrawPile* drawPile;
public:
    ViewDrawPile(Splendor::DrawPile& d, QWidget* parent = nullptr);

signals:
    void drawPileClicked(ViewDrawPile*);
public slots:
private slots:
    void clickedEvent() { emit drawPileClicked(this); }
};

#endif // VUEDRAWPILE_H