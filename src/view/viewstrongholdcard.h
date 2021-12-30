#ifndef VIEWSTRONGHOLDCARD_H
#define VIEWSTRONGHOLDCARD_H

#include "viewresourcecard.h"
#include "viewstronghold.h"

class ViewStrongholdCard : public ViewResourceCard
{
    Q_OBJECT
private:
    ViewStronghold* stronghold;
public:
    ViewStrongholdCard(QWidget* parent = nullptr);

    void updateStronghold();

    ~ViewStrongholdCard();
};

#endif // VIEWSTRONGHOLDCARD_H
