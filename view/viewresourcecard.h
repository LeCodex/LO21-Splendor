#ifndef VUERESOURCECARD_H
#define VUERESOURCECARD_H

#include "vuecard.h"

class VueResourceCard : public VueCard
{
private:
    QImage tokenIcon;
public:
    VueResourceCard(const Splendor::ResourceCard& card, QWidget* parent);
};

#endif // VUERESOURCECARD_H
