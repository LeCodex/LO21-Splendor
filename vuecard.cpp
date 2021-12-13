#include "vuecard.h"

VueCard::VueCard(Splendor::BaseCard* c, QWidget* parent) : QPushButton(parent), card(c)
{
     connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
}
