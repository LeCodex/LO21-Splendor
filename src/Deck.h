#pragma once
#include "card.h"

namespace Splendor {
	class Deck
	{
	private:
		const Card** cards;
		int nb;
		int nbMax;

		Deck();
		~Deck();

		Deck(const Deck&) = delete;
		Deck& operator=(const Deck&) = delete;

		struct Handler {
			Deck* instance;
			Handler() : instance(nullptr) {}
			~Handler() { delete instance; }
		};
		static Handler handler;

		Deck(int n) : nb(0), nbMax(n), cards(new Card*[n]) {}
	public:
		static Deck& instance();
		void deleteInstance();

		int getNbCards() { return nb; }
		const Card** getAllCards() { return cards; }
		const Card& getCard(size_t i) { return *cards[i]; }

		// Add iterator
	};
}

