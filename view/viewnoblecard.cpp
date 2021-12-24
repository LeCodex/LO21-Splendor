#include <random>
#include "viewnoblecard.h"


ViewNobleCard::ViewNobleCard(QWidget* parent) : ViewCard(parent)
{
    setFixedWidth(150);
    setFixedHeight(150);
}

void ViewNobleCard::updateImage() {
    QPixmap pixmap;

    if (!card) {
        pixmap.load(":/general/unknown");
    } else {
        std::string paths[1] = {
            ":/nobles/abbot"
        };
        pixmap.load(paths[rand() % 1].c_str());
    }

    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(120, 120));
}

void ViewNobleCard::updateCost() {
    // Unload cost images to clear them
    for (auto i: costs) i->getImage()->clear();;

    if (!card) {
        return;
    } else {
        std::string icons[6] = {
            ":/cards/red",
            ":/cards/blue",
            ":/cards/green",
            ":/cards/white",
            ":/cards/black"
        };

        size_t j = 0;
        for (size_t i = 0; i < 5; i ++) {
            int c = card->getTokenCost((Splendor::Token)i);

            if (c > 0) {
                QPixmap pixmap(icons[i].c_str());
                costs[j]->getImage()->setPixmap(pixmap);
                costs[j]->getAmount()->display(c);
                j++;
            }
        }
    }
}
