#ifndef DRAWPILE_H
#define DRAWPILE_H

#include <stdlib.h>
#include "basecard.h"

class DrawPile
{
private:
    size_t nb;
    const size_t nbMax;
    BaseCard const **cards;

public:
    // Only constructor, creates an empty array of size _n
    explicit DrawPile(size_t _n) : nbMax(_n), nb(0), cards(new const BaseCard *[_n]) {}

    // Destructor of class, destroy array but not the cards in it
    ~DrawPile()
    {
        delete[] cards;
    }

    // No assignation or copy constructor
    DrawPile &operator=(const DrawPile &) = delete;
    DrawPile(const DrawPile &) = delete;

    // Check if the DrawPile is empty
    bool isEmpty() const { return nb == 0; }

    // Pick a card and returns it (works like a pile)
    const BaseCard &pick()
    {
        // TODO : Creates real errors
        if (isEmpty())
            throw "Pile Vide";
        return *cards[nb--];
    }

    // Add a single cart to the drawpile
    void add(const BaseCard &c)
    {
        // TODO : Creates real errors
        if (nb == nbMax)
            throw "Pile Pleine";
        cards[nb++] = &c;
    }

    // Add a collection of cards to the drawpile
    // TODO : change cs to a collection (with an iterator)
    void add(const BaseCard *&cs, size_t n)
    {
        for (size_t i = 0; i < n; i++)
            add(cs[i]);
    }
};

#endif