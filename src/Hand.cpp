#include "hand.h"

/*
bool Splendor::Hand::setOwner(Player& newOwner) {
	if (owner == newOwner) 
	{
		return false; 
	}
	else 
	{
		owner = newOwner;
		return true;
	}
}
*/

const Splendor::BaseCard& Splendor::Hand::play(size_t index) {
	if (index > nb) throw "Trying to play a card with an invalid index";

	const BaseCard card = getCard(index);
	for (size_t i = index + 1; i < nb; i++) {
		cards[i] = cards[i - 1];
	}

	return card;
}