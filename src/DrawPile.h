#pragma once
#include "ResourceCard.h"

namespace Splendor
{
	class DrawPile
	{
	protected:
		const ResourceCard **cards;
		size_t nb;
		size_t nbMax;

	public:
		explicit DrawPile();

		size_t getCardAmount() const { return nb; }
		bool empty() const { return nb == 0; }
		const ResourceCard &getCard(size_t index);
        const ResourceCard* draw();
		void addCard(const ResourceCard &card);

		DrawPile(DrawPile &) = delete;
		DrawPile &operator=(DrawPile &) = delete;

		class const_iterator
		{
		private:
			const ResourceCard **current = nullptr;
			const_iterator(const ResourceCard **c) : current(c){};

			friend class DrawPile;

		public:
			const ResourceCard &operator*() { return **current; }
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
