#include "board.h"

// Replinishers
void Splendor::Board::fillDrawPile(size_t i, const Splendor::ResourceCard &c)
{
    if (i > 3)
        throw "Index out of bound";
    drawpiles[i].addCard(c);
}

void Splendor::Board::fillNobles(const Splendor::NobleCard &c)
{
    nobles.push_back(&c);
}

// Update functions
void Splendor::Board::replenishCenterCards()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (cards[i][j] == nullptr)
                if (!drawpiles[i].empty())
                    cards[i][j] = &drawpiles[i].draw();
        }
    }
}

// Takers
const Splendor::ResourceCard &Splendor::Board::takeCenterCard(size_t i, size_t j)
{
    if (i > 3 || j > 4)
        throw "Index out of bound\n";
    if (cards[i][j] == nullptr)
        throw "No card here\n";
    const ResourceCard &r = *cards[i][j];

    // Retirer la carte (shift)
    for (size_t k = j; k < 3; k++)
        cards[i][k] = cards[i][k + 1];
    cards[i][3] = nullptr;

    return r;
}
// Surcharge pour la vue
const Splendor::ResourceCard &Splendor::Board::takeCenterCard(const ResourceCard &c)
{
    // On cherche la carte
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 4; j++)
            // Quand on trouve la carte
            if (cards[i][j] == &c)
                return takeCenterCard(i, j);
    throw "Unknown card\n";
}
const Splendor::ResourceCard &Splendor::Board::takeDrawCard(size_t i)
{
    if (i > 3)
        throw "Index out of bound\n";
    return drawpiles[i].draw();
}
const Splendor::NobleCard &Splendor::Board::takeNobleCard(size_t i)
{
    if (i > nobles.size())
        throw "Index out of bound\n";
    const NobleCard &n = *nobles.at(i);
    nobles.erase(nobles.begin() + i);
    return n;
}
// Surcharge pour la vue
const Splendor::NobleCard &Splendor::Board::takeNobleCard(const Splendor::NobleCard &c)
{
    size_t i = 0;
    for (auto it = nobles.begin(); it != nobles.end(); it++, i++)
        if (*it == &c)
            return takeNobleCard(i);
    throw "Unknown card\n";
}