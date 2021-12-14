#include "vueclickable.h"

VueClickable::VueClickable(QWidget* parent): QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
}
