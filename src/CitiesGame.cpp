#include "game.h"

Splendor::CitiesGame::Handler Splendor::CitiesGame::handler;

void Splendor::CitiesGame::addPlayer(std::string name, bool ai, int index)
{
    if (players[index] != nullptr)
        throw "Joueur déjà créé";
    std::cout << "Player \"" << name << "\" has been added to [" << index << "]\n";
    players[index] = (Player*)new CitiesPlayer(name, ai);
}

void Splendor::CitiesGame::cardDistribution()
{
    // We had 3 cities to the Board's noble section (since cities are children of nobles)
    for (size_t i = 0; i < 3; i++)
    {
        // Should be random
        // TODO...
        const CitiesCard& city = cities.getCard(i);
        board.fillNobles(city);
    }

    // We add the resource cards to the drawpile
    vector<const ResourceCard *> rs = getResourceDeck().getAllCards();
    for (auto it = rs.begin(); it != rs.end(); ++it)
    {
        const ResourceCard &resource = **it;
        board.fillDrawPile(resource.getLevel(), resource);
    }
}

void Splendor::CitiesGame::cardLoading()
{
    // Deck must be generated manually
    // Noble deck generation :
    getResourceDeck().loadXML(":/resources/resourcesxml");
    getResourceDeck().shuffle();

    // Ressource deck generation :
    cities.loadXML(":/cities/citiesxml");
    cities.shuffle();
}
