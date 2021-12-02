#pragma once
#include "basecard.h"
#include <vector>

namespace Splendor {
	template <class T>
	class Deck
	{
	private:
		std::vector<const T*> cards;
		int nb;
		int nbMax;

		Deck(const Deck&) = delete;
		Deck& operator=(const Deck&) = delete;
	public:
		Deck() : nb(0), nbMax(10) {}

		int getNbCards() const { return nb; }
		std::vector<const T*> getAllCards() const { return cards; }
		const T& getCard(size_t i) const { return *cards[i]; }
	};
}

