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
