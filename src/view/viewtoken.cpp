#include "viewtoken.h"

ViewToken::ViewToken(Splendor::Token t, QWidget* parent) : ViewClickable(parent), token(t)
{
    setFlat(true);

    number = new QLCDNumber(1);
    number->setMinimumHeight(20);
    number->setFrameStyle(0);
    number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout = new QHBoxLayout();
    layout->addWidget(number, 0, Qt::AlignCenter);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setLayout(layout);

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
    setIconSize(QSize(50, 50));
}

void ViewToken::updateAmount() {
    number->display(amount);
    number->setPalette(Qt::darkGray);

    if (amount == 0)
        number->setPalette(Qt::red);
}
