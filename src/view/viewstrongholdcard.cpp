#include "viewstrongholdcard.h"

ViewStrongholdCard::ViewStrongholdCard(QWidget* parent) : ViewResourceCard(parent)
{
    stronghold = new ViewStronghold();

    rightLayout->addWidget(stronghold);
}

void ViewStrongholdCard::updateStronghold() {

}

ViewStrongholdCard::~ViewStrongholdCard()
{
    delete stronghold;
}
