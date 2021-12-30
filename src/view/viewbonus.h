#ifndef VIEWBONUS_H
#define VIEWBONUS_H

#include "viewclickable.h"
#include <QLCDNumber>
#include <QLayout>

class ViewBonus : public ViewClickable
{
    Q_OBJECT
private:
    QLCDNumber* number;
    QHBoxLayout* layout;
public:
    explicit ViewBonus(std::string& path, QWidget *parent = nullptr);
    void updateIcon(std::string& path);
    void updateAmount(int amount);

    ~ViewBonus();

signals:
    void bonusClicked(ViewBonus*);
public slots:
private slots:
    void clickedEvent() { emit bonusClicked(this); }
};

#endif // VIEWBONUS_H
