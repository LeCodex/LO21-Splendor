#ifndef SPLENDOR_H
#define SPLENDOR_H

// UNIQUEMENT CREEE POUR AVOIR ACCES AUX DIFFERENTS TRUCS DONT J'AVAIS BESOIN, NON FONCTIONNELLE, A REMPLACER

#include <iostream>
#include <vector>

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
        int cost[5];
    public:
        BaseCard(int p = 0): prestige(p) {}
        int getPrestige() const { return prestige; }
        void setPrestige(int p) { prestige = p; }
        int getTokenCost(Token t) const { return cost[t]; }
        void setCost(int c[5]) { for (size_t i = 0; i < 5; i ++) cost[i] = c[i]; }
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

    class Bank {
    private:
        int tokens[6]{ 0, 0, 0, 0, 0, 0 };

    public:
        Bank(int t[] = nullptr) {
            if (t)
                for (size_t i = 0; i < 6; i++) {
                    tokens[i] = t[i];
                }
        }

        bool empty(Token t) const { return tokens[t] == 0; }
        int amount(Token t) const { return tokens[t]; }
        const int* getAll() const { return tokens; }
        int take(Token t, int amount);
        int put(Token t, int amount);
    };

    class Board {
    private:
        const ResourceCard *cards[3][4];
        Bank bank;
        DrawPile drawpiles[3];
        std::vector<const NobleCard *> nobles;

    public:
        Board() = default;
        ~Board() = default;

        // Getters
        const ResourceCard &getCard(size_t i, size_t j) { return *cards[i][j]; };
        Bank &getBank() { return bank; }
        DrawPile &getDrawPile(size_t i) { return drawpiles[i]; };
        std::vector<NobleCard const *> getNobles() { return nobles; };
    };

    class Player {
    private:
        const std::string name;
        Bank bank;
        std::vector<const ResourceCard *> ressource[3];
        std::vector<const NobleCard *> nobles;
        const ResourceCard *ReservedCards[3];

    public:
        Player(std::string s) : name(s)
        {
            for (size_t i = 0; i < 3; i++)
                ReservedCards[i] = nullptr;
        }

        ~Player() = default;

        Bank getBank() { return bank; }
        std::string getName() { return name; }
        int *getBonuses() { return 0; }
        int getPoint() { return 10; }

        std::vector<const ResourceCard *> getRessources(size_t i) const { return ressource[i]; }
        std::vector<const NobleCard *> getNobles() const { return nobles; }
        const ResourceCard *getReservedCards(size_t i) const { return ReservedCards[i]; }
    };

    class Game {
    private:
        size_t nb;
        size_t current;
    public:
        Game(size_t n): nb(n), current(0) {}
        size_t getNbPlayers() const { return nb; }
        size_t getCurrent() const { return current; }
    };
}

#endif // SPLENDOR_H
