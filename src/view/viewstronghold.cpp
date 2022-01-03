#include "viewcities.h"

ViewCities::ViewCities(QWidget *parent) : QPushButton(parent)
{
    amount = new QLCDNumber();
    amount->display(0);
    amount->setFrameStyle(0);

    name = new QLabel();
    name->setAlignment(Qt::AlignCenter);

    layer = new QVBoxLayout();
    layer->addWidget(amount);
    layer->addWidget(name);

    QPixmap pixmap(":/general/cities");
    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(30, 30));
}

void ViewCities::setOwner(std::string n, int a) {
    name->setText(n.c_str());
    amount->display(a);
}

ViewCities::~ViewCities()
{
    delete amount;
    delete name;
    delete layer;
}
