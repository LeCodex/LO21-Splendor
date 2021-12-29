#ifndef VIEWCOST_H
#define VIEWCOST_H

#include <QWidget>
#include <QLCDNumber>
#include <QLabel>

class ViewCost : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber* amount;
public:
    explicit ViewCost(QWidget *parent = nullptr);

    QLCDNumber* getAmount() const { return amount; }

    ~ViewCost();
};

#endif // VIEWCOST_H
