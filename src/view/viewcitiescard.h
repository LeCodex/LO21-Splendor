#ifndef VIEWCITIESCARD_H
#define VIEWCITIESCARD_H

#include "viewnoblecard.h"

class ViewCitiesCard : public ViewNobleCard
{
    Q_OBJECT
private:
    ViewCost* extraCost;
protected:
    void updateImage() override;
    void updateCost() override;
public:
    ViewCitiesCard(QWidget* parent = nullptr);
    ~ViewCitiesCard();
};

#endif // VIEWCITIESCARD_H
