#ifndef VUEDRAWPILE_H
#define VUEDRAWPILE_H

#include <QWidget>
#include <QPushButton>
#include "vueclickable.h"

class VueDrawPile : public VueClickable
{
    Q_OBJECT
private:
    QImage back;
public:
    VueDrawPile(QWidget* parent);

signals:
    void drawPileClicked(VueDrawPile*);
public slots:
private slots:
    void clickedEvent() { emit drawPileClicked(this); }
};

#endif // VUEDRAWPILE_H
