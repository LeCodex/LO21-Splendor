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
            ":/cards/white",
            ":/cards/blue",
            ":/cards/green",
            ":/cards/red",
            ":/cards/black"
        };
        pixmap.load(paths[((const Splendor::ResourceCard*) card)->getResource()].c_str());
    }

    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(75, 75));
}
