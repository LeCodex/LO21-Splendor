#ifndef SPLENDOR_H
#define SPLENDOR_H

namespace Splendor {
    enum Token {};
    class BaseCard {};
    class NobleCard : public BaseCard {};
    class ResourceCard : public BaseCard {};
    class Deck {};
    class DrawPile {};
    class Bank {};
    class Board {};

    class Player {};

    class Game {};

    class Controller {};
}

#endif // SPLENDOR_H
