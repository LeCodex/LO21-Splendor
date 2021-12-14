#ifndef VUERESOURCECARD_H
#define VUERESOURCECARD_H

#include "viewcard.h"

class ViewResourceCard : public ViewCard
{
private:
    QImage tokenIcon;
public:
    ViewResourceCard(const Splendor::ResourceCard& card, QWidget* parent);
};

#endif // VUERESOURCECARD_H
