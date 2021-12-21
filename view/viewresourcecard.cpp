#include "viewresourcecard.h"

ViewResourceCard::ViewResourceCard(QWidget* parent) : ViewCard(parent)
{

}

void ViewResourceCard::updateImage() {
    QPixmap pixmap;

    if (!card) {
        pixmap.load(":/general/unknown");
    } else {
        std::string paths[6] = {
            ":/cards/red",
            ":/cards/blue",
            ":/cards/green",
            ":/cards/white",
            ":/cards/black"
        };
        pixmap.load(paths[rand() % 6].c_str());
    }

    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(100, 100));
}
