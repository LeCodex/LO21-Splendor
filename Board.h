#pragma once
#include "BaseCard.h"
#include "Bank.h"
namespace Splendor {
    class Board
    {
    private:
        const BaseCard** cards = new const BaseCard*();
        size_t nb;
        size_t nb_max;
        Bank bank;
        const BaseCard* getBaseCard(size_t i) const { return cards[i]; }
    public:
        Board();
        Board(const Board& plateau);
        void operator=(const Board& plateau1);

        size_t getNb() const { return nb; }
        size_t getNbMax() const { return nb_max; }

        void addCard(const BaseCard& carte);
        void removeCard(const BaseCard& carte);
        Bank& getBank(){ return bank ;}
        class const_iterator {
        private:
            const BaseCard** current = nullptr;
            const_iterator(const BaseCard** c) : current(c) {};

            friend class Board;
        public:
            const BaseCard& operator*() { return **current; }
            const_iterator& operator++() { current++; return *this; }
            bool operator!=(const_iterator it) { return current != it.current; }
        };
        const_iterator begin() const { return const_iterator(cards); }
        const_iterator end() const { return const_iterator(cards + nb); }

        ~Board() { delete cards; }
    };
}

std::ostream& operator<<(std::ostream&, const Splendor::Board&);
