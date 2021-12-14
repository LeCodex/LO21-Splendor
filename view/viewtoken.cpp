#include "viewtoken.h"

ViewToken::ViewToken(Splendor::Token t, QWidget* parent) : QPushButton(parent), token(t)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
}
