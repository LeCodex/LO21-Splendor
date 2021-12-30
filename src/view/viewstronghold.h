#ifndef VIEWSTRONGHOLD_H
#define VIEWSTRONGHOLD_H

#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>
#include <QLayout>

class ViewStronghold : public QPushButton
{
    Q_OBJECT
private:
    QLCDNumber* amount;
    QLabel* name;
    QVBoxLayout* layer;
public:
    explicit ViewStronghold(QWidget *parent = nullptr);
    void setOwner(std::string name, int amount);

    ~ViewStronghold();
signals:

};

#endif // VIEWSTRONGHOLD_H
