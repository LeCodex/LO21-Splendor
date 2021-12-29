#include <random>
#include "viewnoblecard.h"


ViewNobleCard::ViewNobleCard(QWidget* parent) : ViewCard(parent)
{
    costLayout->setDirection(QBoxLayout::Direction::LeftToRight);
    layer->setDirection(QBoxLayout::Direction::TopToBottom);
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
    setIconSize(QSize(75, 75));
}
