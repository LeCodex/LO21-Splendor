#pragma once
#include "basecard.h"

namespace Splendor {
	class DrawPile {
	private:
		std::vector<const BaseCard*> cards;

		DrawPile(DrawPile&) = delete;
		DrawPile& operator=(DrawPile&) = delete;
	public:
		DrawPile() {}

		size_t getCardAmount() const { return cards.size(); }
		bool empty() const { return getCardAmount() == 0; }
		const BaseCard& getCard(size_t index);
		const BaseCard& draw();
		void addCard(const BaseCard& card);
	};
}

