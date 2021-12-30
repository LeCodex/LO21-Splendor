#include "viewbonus.h"

ViewBonus::ViewBonus(std::string& path, QWidget *parent) : ViewClickable(parent)
{   
    number = new QLCDNumber(1);
    number->display(0);
    number->setMinimumHeight(40);
    number->setFrameStyle(0);

    layout = new QHBoxLayout();
    layout->addWidget(number, 0, Qt::AlignCenter);

    if (path.length() == 0) path = ":/general/unknown";
    updateIcon(path);

    setLayout(layout);
}

void ViewBonus::updateIcon(std::string& path) {
    QPixmap pixmap(path.c_str());
    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(100, 100));
}

void ViewBonus::updateAmount(int amount) {
    number->display(amount);
}

ViewBonus::~ViewBonus() {
    delete layout;
    delete number;
}
