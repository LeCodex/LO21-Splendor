#include "drawpile.h"
#include <random>

Splendor::DrawPile::DrawPile() : nb(0), cards(new const BaseCard*[10]) {}

const Splendor::BaseCard& Splendor::DrawPile::draw()
{
	if (empty()) throw "Trying to draw from an empty draw pile";

	int index = rand() % nb;
	const BaseCard* card = cards[index];

	for (size_t i = index + 1; i < nb; i++) {
		cards[i-1] = cards[i];
	}
	nb--;

	return *card;
}

void Splendor::DrawPile::addCard(const BaseCard& card) {
	if (nb == nbMax) {
		const BaseCard** tab = new const BaseCard*[nb + 20];

		for (size_t i = 0; i < nb; i++) {
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