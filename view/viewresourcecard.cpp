#include "viewresourcecard.h"

ViewResourceCard::ViewResourceCard(QWidget* parent) : ViewCard(parent)
{

}

void ViewResourceCard::updateImage() {
    QPixmap pixmap;

    if (!card) {
        pixmap.load(":/general/unknown");
    } else {
        std::string paths[5] = {
            ":/cards/red",
            ":/cards/blue",
            ":/cards/green",
            ":/cards/white",
            ":/cards/black"
        };
        pixmap.load(paths[dynamic_cast<const Splendor::ResourceCard*>(card)->getToken()].c_str());
    }

    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(100, 100));
}

void ViewResourceCard::updateCost() {
    // Hide
    for (auto i: costs) {
        i->getImage()->hide();
        i->getAmount()->hide();
    }

    if (!card) {
        return;
    } else {
        std::string icons[6] = {
            ":/tokens/red",
            ":/tokens/blue",
            ":/tokens/green",
            ":/tokens/white",
            ":/tokens/black"
        };

        size_t j = 0;
        for (size_t i = 0; i < 5; i ++) {
            int c = card->getTokenCost((Splendor::Token)i);

            if (c > 0) {
                QPixmap pixmap(icons[i].c_str());
                costs[j]->getImage()->setPixmap(pixmap);
                costs[j]->getImage()->show();
                costs[j]->getAmount()->display(c);
                costs[j]->getAmount()->show();
                j++;
            }
        }
    }
}
