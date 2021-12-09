#pragma once
#include "BaseCard.h"

namespace Splendor
{
	class DrawPile
	{
	protected:
		const BaseCard **cards;
		size_t nb;
		size_t nbMax;

	public:
		explicit DrawPile();

		size_t getCardAmount() const { return nb; }
		bool empty() const { return nb == 0; }
		const BaseCard &getCard(size_t index);
		const BaseCard &draw();
		void addCard(const BaseCard &card);

		DrawPile(DrawPile &) = delete;
		DrawPile &operator=(DrawPile &) = delete;

		class const_iterator
		{
		private:
			const BaseCard **current = nullptr;
			const_iterator(const BaseCard **c) : current(c){};

			friend class DrawPile;

		public:
			const BaseCard &operator*() { return **current; }
			const_iterator operator++()
			{
				current++;
				return *this;
			}
			bool operator!=(const const_iterator &it) { return current != it.current; }
		};
		const_iterator begin() const { return const_iterator(cards); }
		const_iterator end() const { return const_iterator(cards + nb); }

		~DrawPile() { delete[] cards; }
	};
}
