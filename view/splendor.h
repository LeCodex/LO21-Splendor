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

    class BaseCard {
    private:
        int prestige;
    public:
        BaseCard(int p = 0): prestige(p) {}
        int getPrestige() const { return prestige; }
        void setPrestige(int p) { prestige = p; }
        virtual ~BaseCard() = default;
    };
    class NobleCard : public BaseCard {
    public:
        NobleCard(int p): BaseCard(p) {}
    };
    class ResourceCard : public BaseCard {
    private:
        Token token;
    public:
        ResourceCard(Token t = Red, int p = 0): BaseCard(p), token(t) {}
        Token getToken() const { return token; }
        void setToken(Token t) { token = t; }
    };

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
