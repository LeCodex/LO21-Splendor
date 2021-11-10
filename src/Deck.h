#pragma once
#include "basecard.h"

namespace Splendor {
	class Deck
	{
	private:
		const BaseCard** cards;

		Deck(const Deck&) = delete;
		Deck& operator=(const Deck&) = delete;

		// Singleton handler
		struct Handler {
			Deck* instance;
			Handler() : instance(nullptr) {}
			~Handler() { delete instance; }
		};
		static Handler handler;

		Deck(int n) : nb(0), nbMax(n), cards(new const BaseCard*[n]) {}

	protected:
		int nb;
		int nbMax;

		Deck();
		~Deck();
	
	public:
		static Deck& instance();
		void deleteInstance();

		int getNbCards() const { return nb; }
		const BaseCard** getAllCards() const { return cards; }
		const BaseCard& getCard(size_t i) const { return *cards[i]; }

		class Iterator {
		private:
			const BaseCard** current;
			Iterator(const BaseCard** start) : current(start) {};
			friend class Deck;

		public:
			const BaseCard& operator*() { return **current; }
			Iterator operator++() { return ++current; }
			bool operator!=(Iterator& it) { return current != it.current; }
		};
		Iterator begin() const { return Iterator(cards); }
		Iterator end() const { return Iterator(cards + nb); }
	};
}

