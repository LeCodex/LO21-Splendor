#ifndef VUECLICKABLE_H
#define VUECLICKABLE_H

#include <QPushButton>
#include <QWidget>

class VueClickable : public QPushButton
{
    Q_OBJECT
public:
    VueClickable(QWidget* parent);

private slots:
    virtual void clickedEvent() = 0;
};

#endif // VUECLICKABLE_H
