#include "viewcard.h"

ViewCard::ViewCard(const Splendor::BaseCard* c, QWidget* parent) : ViewClickable(parent), card(c)
{
    setFixedWidth(150);
    setFixedHeight(200);
}
