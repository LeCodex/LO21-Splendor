#pragma once
#include "basecard.h"
#include <vector>

namespace Splendor {
	template <class T>
	class Deck
	{
	private:
		std::vector<const T*> cards;

		Deck(const Deck&) = delete;
		Deck& operator=(const Deck&) = delete;
	public:
		Deck(std::string data) : cards() {}

		int getNbCards() const { return cards.size(); }
		std::vector<const T*> getCards() const { return cards; }
		const T& getCard(size_t i) const { return *cards[i]; }
	};
}

