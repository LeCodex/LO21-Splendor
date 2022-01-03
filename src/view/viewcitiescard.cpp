#include "viewcitiescard.h"

ViewCitiesCard::ViewCitiesCard(QWidget* parent) : ViewNobleCard(parent) {
    extraCost = new ViewCost();
    costLayout->addWidget(extraCost);
}

void ViewCitiesCard::updateImage() {
    QPixmap pixmap;

    if (!card) {
        pixmap.load(":/general/unknown");
    } else {
        std::string paths[1] = {
            ":/cities/cathedral"
        };
        pixmap.load(paths[rand() % 1].c_str());
    }

    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(75, 75));
}

void ViewCitiesCard::updateCost() {
    // Hide
    for (auto i: costs) {
        i->getAmount()->hide();
    }
    extraCost->getAmount()->hide();

    if (!card) {
        return;
    } else {
        Qt::GlobalColor colors[5] {
            Qt::white,
            Qt::blue,
            Qt::green,
            Qt::red,
            Qt::black
        };

        size_t j = 0;
        for (size_t i = 0; i < 5; i ++) {
            int c = card->getCost((Splendor::Token)i);

            // qInfo() << QString::fromStdString(Splendor::getTokenName((Splendor::Token) i)) << " : " << c << "\n";

            if (c > 0) {
                costs[j]->getAmount()->display(c);
                costs[j]->getAmount()->setPalette(colors[i]);
                costs[j]->getAmount()->show();
                j++;
            }
        }

        Splendor::CitiesCard* cityCard = (Splendor::CitiesCard*)card;
        int otherCost = cityCard->getOtherCost();
        if (otherCost) {
            extraCost->getAmount()->display(otherCost);
            extraCost->getAmount()->setPalette(Qt::magenta);
            extraCost->getAmount()->show();
        }
    }
}

ViewCitiesCard::~ViewCitiesCard() { delete extraCost; }
