#ifndef VUERESOURCECARD_H
#define VUERESOURCECARD_H

#include "viewcard.h"

class ViewResourceCard : public ViewCard
{
    Q_OBJECT
protected:
    void updateImage() override;
public:
    ViewResourceCard(QWidget* parent = nullptr);
};

#endif // VUERESOURCECARD_H
