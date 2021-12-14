#ifndef SPLENDOR_H
#define SPLENDOR_H

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

    class Game {};
}

#endif // SPLENDOR_H
