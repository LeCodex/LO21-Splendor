#include <random>
#include "drawpile.h"

const Splendor::BaseCard& Splendor::DrawPile::getCard(size_t index) {
	if (index > cards.size()) throw "Trying to access a card outside a DrawPile's range";

	return *cards[index];
}

const Splendor::BaseCard& Splendor::DrawPile::draw() {
	if (empty()) throw "Trying to draw from an empty draw pile";

	int index = rand() % cards.size();
	return **cards.erase(cards.begin() + 1);
}

void Splendor::DrawPile::addCard(const BaseCard& card) {
	cards.push_back(&card);
}