#ifndef VIEWTOKEN_H
#define VIEWTOKEN_H

#include <QWidget>
#include <QLCDNumber>
#include <QLayout>
#include "splendor.h"
#include "viewclickable.h"

class ViewToken : public ViewClickable
{
    Q_OBJECT
private:
    Splendor::Token token;
    int amount = 0;
    QLCDNumber* number;
    QHBoxLayout* layout;

    void updateIcon();
    void updateAmount();
public:
    ViewToken(Splendor::Token t, QWidget* parent = nullptr);
    void setAmount(int a) { amount = a; updateAmount(); }
    int getAmount() const { return amount; }
    void setToken(Splendor::Token t) { token = t; updateIcon(); }
    Splendor::Token getToken() const { return token; }

signals:
    void tokenClicked(ViewToken*);
public slots:
private slots:
    void clickedEvent() { emit tokenClicked(this); }
};

#endif // VIEWTOKEN_H
