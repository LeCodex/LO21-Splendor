#ifndef VUETOKEN_H
#define VUETOKEN_H

#include <QPushButton>
#include <QWidget>
#include "splendor.h"

class VueToken : public QPushButton
{
    Q_OBJECT
private:
    Splendor::Token token;
    int amount = 0;
public:
    VueToken(Splendor::Token t, QWidget* parent);
    void setAmount(int a) { amount = a; }
    int getAmount() const { return amount; }
    void setToken(Splendor::Token t) { token = t; }
    Splendor::Token getToken() const { return token; }

signals:
    void tokenClicked(VueToken*);
public slots:
private slots:
    void clickedEvent() { emit tokenClicked(this); }
};

#endif // VUETOKEN_H
