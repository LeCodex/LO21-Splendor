#ifndef VUENOBLECARD_H
#define VUENOBLECARD_H

#include "vuecard.h"

class VueNobleCard : public VueCard
{
public:
    VueNobleCard(const Splendor::NobleCard& card, QWidget* parent);
};

#endif // VUENOBLECARD_H
