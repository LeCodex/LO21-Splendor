#pragma once
#include "basecard.h"

namespace Splendor {
	class Deck
	{
	private:
		BaseCard** cards;

		Deck(const Deck&) = delete;
		Deck& operator=(const Deck&) = delete;

		// Singleton handler
		struct Handler {
			Deck* instance;
			Handler() : instance(nullptr) {}
			~Handler() { delete instance; }
		};
		static Handler handler;

		Deck(int n) : nb(0), nbMax(n), cards(new BaseCard*[n]) {}

	protected:
		int nb;
		int nbMax;

		Deck();
		~Deck();
	
	public:
		static Deck& instance();
		void deleteInstance();

		int getNbCards() const { return nb; }
		BaseCard** getAllCards() const { return cards; }
		BaseCard& getCard(size_t i) const { return *cards[i]; }

		class Iterator {
		private:
			BaseCard** current;
			Iterator(BaseCard** start) : current(start) {};
			friend class Deck;

		public:
			BaseCard& operator*() { return **current; }
			Iterator operator++() { return ++current; }
			bool operator!=(Iterator& it) { return current != it.current; }
		};
		Iterator begin() { return Iterator(cards); }
		Iterator end() { return Iterator(cards + nb); }
	};
}

