#ifndef VIEWNOBLECARD_H
#define VIEWNOBLECARD_H

#include "viewcard.h"

class ViewNobleCard : public ViewCard
{
public:
    ViewNobleCard(const Splendor::NobleCard& card, QWidget* parent);
};

#endif // VIEWNOBLECARD_H
