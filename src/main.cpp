#include "game.h"
#include "controller.h"
#include "Deck.h"

using namespace Splendor;

int main()
{
    Game &g = Game::getInstance(3);
    g.addPlayer("joueur#0", 0);
    g.deleteInstance();

    // TextualController c;
    // c.initiateGame();

    try
    {
        Deck<ResourceCard> dr;
        dr.loadXML("filename");
    }
    catch (char const *e)
    {
        std::cout << e << "\n";
    }
    catch (...)
    {
        std::cout << "Erreur :(\n";
    }

    std::cout << "Done\n";
    // Deck<NobleCard> dn;
    // dn.loadXML("filename");

    return 0;
}