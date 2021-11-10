#pragma once
#include "basecard.h"

namespace Splendor {
	class Deck
	{
	private:
		const BaseCard** cards;
		int nb;
		int nbMax;

		Deck();
		~Deck();

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
	public:
		static Deck& instance();
		void deleteInstance();

		int getNbCards() const { return nb; }
		const BaseCard** getAllCards() const { return cards; }
		const BaseCard& getCard(size_t i) const { return *cards[i]; }

		class const_iterator {
		private:
			const BaseCard** current = nullptr;
			const_iterator(const BaseCard** c) : current(c) {};

			friend class Deck;
		public:
			const BaseCard& operator*() { return **current; }
			const_iterator operator++() { current++; return *this; }
			bool operator!=(const_iterator& it) { return current != it.current; }
		};
		const_iterator begin() const { return const_iterator(cards); }
		const_iterator end() const { return const_iterator(cards + nb); }
	};
}

