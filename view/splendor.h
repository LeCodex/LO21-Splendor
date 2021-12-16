#ifndef SPLENDOR_H
#define SPLENDOR_H

#include <iostream>

namespace Splendor {
    enum Token {
        Red,
        Blue,
        Green,
        White,
        Black,
        Gold
    };
    class BaseCard {};
    class NobleCard : public BaseCard {};
    class ResourceCard : public BaseCard {};
    class Deck {};
    class DrawPile {};
    class Bank {};
    class Board {};

    class Player {};

    class Game {
    private:
        size_t nb;
    public:
        Game(size_t n): nb(n) {}
        size_t getNbPlayers() const { return nb; }
    };
}

#endif // SPLENDOR_H
