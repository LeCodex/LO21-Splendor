#include "deck.h"

Splendor::Deck::Deck() : nb(0), nbMax(10) {
    cards = new const BaseCard*[nbMax];
}

Splendor::Deck& Splendor::Deck::getInstance() {
    if (handler.instance == nullptr) handler.instance = new Deck;
    return *handler.instance;
}

void Splendor::Deck::deleteInstance() {
    delete handler.instance;
    handler.instance = nullptr;
}

Splendor::Deck::~Deck() {
    for (size_t i = 0; i < nb; i++) {
        delete cards[i];
    }
}

Splendor::Deck::Handler Splendor::Deck::handler;