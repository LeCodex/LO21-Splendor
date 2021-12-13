#include "vuetoken.h"

VueToken::VueToken(Splendor::Token t, QWidget* parent) : QPushButton(parent), token(t)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
}
