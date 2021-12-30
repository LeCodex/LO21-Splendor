#ifndef VIEWNOBLECARD_H
#define VIEWNOBLECARD_H

#include "viewcard.h"

class ViewNobleCard : public ViewCard
{
    Q_OBJECT
protected:
    void updateImage() override;
public:
    ViewNobleCard(QWidget* parent = nullptr);
};

#endif // VIEWNOBLECARD_H
