#ifndef VUEBOARD_H
#define VUEBOARD_H

#include <QWidget>
#include <QLayout>

class VueBoard : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* resourceCardsLayout;
    QVBoxLayout* centralBankLayout;
    QHBoxLayout* nobleCardsLayout;
public:
    explicit VueBoard(QWidget *parent = nullptr);

signals:

};

#endif // VUEBOARD_H
