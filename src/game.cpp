#include "game.h"

// Instantiation of the handler
Splendor::Game::Handler Splendor::Game::handler;

// Base constructor
Splendor::Game::Game(size_t n) : nb_players(n), players(new Player *[n])
{
    try
    {
        // Base initalisation

        // Board is auto generated

        // Players must be initiated with the addPlayer method

        // Deck must be generated manually

        // Noble deck generation :
        resources.loadXML("../data/resources.xml");

        // Ressource deck generation :
        nobles.loadXML("../data/nobles.xml");

        // Board card distribution
        cardDistribution();

        // Fill the middle board
        board.replenishCenterCards();
    }
    catch (char const *s)
    {
        std::cout << s << "\n";
    }
    catch (...)
    {
        std::cout << "Unknown error\n";
    }
}

void Splendor::Game::cardDistribution()
{
    // Distribution of the nobles
    int n = Splendor::Rules::getNumberOfNobles(nb_players);

    // We had n nobles to the Board's noble section
    for (size_t i = 0; i < n; i++)
    {
        // Should be random
        // TODO...
        const NobleCard &noble = nobles.getCard(i);
        board.fillNobles(noble);
    }

    // We add the resource cards to the drawpile
    vector<const ResourceCard *> rs = resources.getAllCards();
    for (auto it = rs.begin(); it != rs.end(); ++it)
    {
        const ResourceCard &resource = **it;
        board.fillDrawPile(resource.getLevel(), resource);
    }
}

Splendor::Game::~Game()
{
    // Deleting the players
    for (size_t i = 0; i < nb_players; i++)
        delete players[i];
    delete[] players;
}

void Splendor::Game::addPlayer(std::string name, int index)
{
    if (players[index] != NULL)
        throw "Joueur déjà créé";
    std::cout << "Player \"" << name << "\" has been added to [" << index << "]\n";
    players[index] = new Player(name);
}
