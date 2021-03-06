#ifndef VUECLICKABLE_H
#define VUECLICKABLE_H

#include <QPushButton>
#include <QWidget>

class ViewClickable : public QPushButton
{
    Q_OBJECT
public:
    ViewClickable(QWidget* parent = nullptr);
    virtual ~ViewClickable() = default;

private slots:
    virtual void clickedEvent() = 0;
};

#endif // VUECLICKABLE_H
