#include "board.h"

Splendor::Board::Board() : nb_max(10), nb(0) {
	cards = new const BaseCard*[nb_max];
}

Splendor::Board::Board(const Board& board) : nb(board.nb), nb_max(board.nb_max) {
	cards = new const BaseCard*[nb_max];

	for (size_t i = 0; i < nb_max; i++)
	{
		cards[i] = board.cards[i];
	}
}

void Splendor::Board::operator=(const Board& board) {
	nb = board.nb;
	nb_max = board.nb_max;

	for (size_t i = 0; i < nb; i++)
	{
		cards[i] = board.cards[i];
	}
}

void Splendor::Board::addCard(const BaseCard& carte) {
	if (nb == nb_max) {
		const BaseCard** new_tab = new const BaseCard*[nb_max * 2];
		for (size_t i = 0; i < nb; i++) new_tab[i] = cards[i];
		nb_max *= 2;

		auto old = cards;
		cards = new_tab;
		delete[] old;
	}

	cards[nb] = &carte;
	nb++;
}

void Splendor::Board::removeCard(const BaseCard& carte) {
	bool shift = false;
	for (size_t i = 0; i < nb; i++)
	{
		if (cards[i] == &carte) {
			shift = true;
			cards[i] = nullptr;
		}
		else if (shift) 
		{
			cards[i] = cards[i - 1];
		}
	}
}

//std::ostream& operator<<(std::ostream& out, const Splendor::Board& board) {
//	out << "Le board est constitué de:\n";
//	for (Splendor::Board::const_iterator it = board.begin(); it != board.end(); ++it) {
//		out << *it << "\n";
//	}
//
//	return out;
//}