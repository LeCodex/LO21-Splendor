#pragma once
#include "basecard.h"

namespace Splendor {
	class DrawPile {
	private:
		const BaseCard** cards;
		size_t nb;
		size_t nbMax;

	public:
		explicit DrawPile();

		size_t getCardAmount() const { return nb; }
		bool empty() const { return nb == 0; }
		const BaseCard& draw();
		void addCard(const BaseCard& card);

		DrawPile(DrawPile&) = delete;
		DrawPile& operator=(DrawPile&) = delete;

		~DrawPile() { delete[] cards; }
	};
}

