#include "vuedrawpile.h"

VueDrawPile::VueDrawPile(QWidget* parent): VueClickable(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
}
