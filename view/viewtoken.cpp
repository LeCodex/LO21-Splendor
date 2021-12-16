#include "viewtoken.h"

ViewToken::ViewToken(Splendor::Token t, QWidget* parent) : ViewClickable(parent), token(t)
{
    setFixedWidth(100);
    setFixedHeight(100);
    setFlat(true);

    number = new QLCDNumber(this);
    number->setGeometry(0, 0, 100, 100);
    number->setFrameStyle(0);

    updateIcon();
    updateAmount();
}

void ViewToken::updateIcon() {
    std::string paths[6] = {
        ":/tokens/red",
        ":/tokens/blue",
        ":/tokens/green",
        ":/tokens/white",
        ":/tokens/black",
        ":/tokens/gold"
    };

    QPixmap pixmap(paths[token].c_str());
    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(100, 100));
}

void ViewToken::updateAmount() {
    number->display(amount);
    number->setPalette(Qt::black);

    if (amount == 0)
        number->setPalette(Qt::red);
}
