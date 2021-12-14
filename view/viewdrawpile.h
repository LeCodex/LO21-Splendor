#ifndef VUEDRAWPILE_H
#define VUEDRAWPILE_H

#include <QWidget>
#include <QPushButton>
#include "viewclickable.h"

class ViewDrawPile : public ViewClickable
{
    Q_OBJECT
private:
    QImage back;
public:
    ViewDrawPile(QWidget* parent);

signals:
    void drawPileClicked(ViewDrawPile*);
public slots:
private slots:
    void clickedEvent() { emit drawPileClicked(this); }
};

#endif // VUEDRAWPILE_H
