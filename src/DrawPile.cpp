#include "DrawPile.h"
#include <random>

Splendor::DrawPile::DrawPile() : nb(0), nbMax(10), cards(new const ResourceCard *[10]) {}

const Splendor::ResourceCard &Splendor::DrawPile::getCard(size_t index)
{
	if (index > nb)
		throw "Trying to access a card outside a DrawPile's range";

	return **(cards + index);
}

const Splendor::ResourceCard* Splendor::DrawPile::draw()
{
	if (empty())
        return nullptr;

	int index = rand() % nb;
	const ResourceCard *card = cards[index];

	for (size_t i = index + 1; i < nb; i++)
	{
		cards[i - 1] = cards[i];
	}
	nb--;

    return card;
}

void Splendor::DrawPile::addCard(const ResourceCard &card)
{
	if (nb == nbMax)
	{
		const ResourceCard **tab = new const ResourceCard *[nb + 20];

		for (size_t i = 0; i < nb; i++)
		{
			tab[i] = cards[i];
		}

		auto old = cards;
		cards = tab;
		delete[] old;

		nbMax += 20;
	}

	cards[nb] = &card;
	nb++;
}
