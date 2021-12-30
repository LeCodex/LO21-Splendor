#include "viewstronghold.h"

ViewStronghold::ViewStronghold(QWidget *parent) : QPushButton(parent)
{
    amount = new QLCDNumber();
    amount->display(0);
    amount->setFrameStyle(0);

    name = new QLabel();
    name->setAlignment(Qt::AlignCenter);

    layer = new QVBoxLayout();
    layer->addWidget(amount);
    layer->addWidget(name);

    QPixmap pixmap(":/general/stronghold");
    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(30, 30));
}

void ViewStronghold::setOwner(std::string n, int a) {
    name->setText(n.c_str());
    amount->display(a);
}

ViewStronghold::~ViewStronghold()
{
    delete amount;
    delete name;
    delete layer;
}
