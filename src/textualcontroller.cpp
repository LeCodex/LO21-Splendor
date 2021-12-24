#include "controller.h"

void Splendor::TextualController::initiateGame()
{
    // Ask for number of players
    std::cout << "Please enter the number of player that are playing.\n";

    // Store it
    int n;
    std::cin >> n;

    // Delete the game if it exists
    Game::deleteInstance();

    // Instanciate the game
    Game &game = Game::createInstance(n);

    std::cout << "A " << n << " players game has been created.\n";

    // Adding n players
    for (size_t i = 0; i < n; i++)
    {
        string s;

        std::cout << "Please enter the name of player #" << i << "\n";
        std::cin >> s;

        game.addPlayer(s, i);
    }
}

void Splendor::TextualController::printGame()
{
    // We get the game instance
    // -1 is to make sure the game is created (if not, provoke an error)
    Game &game = Game::getInstance();

    Board &board = game.getBoard();

    // Printing the nobles
    std::vector<const NobleCard *> nobles = board.getNobles();
    for (size_t i = 0; i < nobles.size(); i++)
    {
        std::cout << "[" << nobles[i]->toString() << "]";
    }
    std::cout << "\n";

    // Printing the middle board
    for (size_t i = 0; i < 3; i++)
    {
        std::cout << "[Lvl : " << (i + 1) << "][Remaining : " << board.getDrawPile(i).getCardAmount() << "]";
        for (size_t j = 0; j < 4; j++)
        {
            try
            {
                std::string s = board.getCard(i, j).toString();
                std::cout << "[" << s << "]";
            }
            catch (const char *)
            {
                // If there is no card
                std::cout << "[ ]";
            }
        }
        std::cout << "\n";
    }

    // Printing player hand
    Player &p = game.getPlayer(actual_player);
    std::cout << "Player #" << actual_player << " (" << p.getName() << "):\n";

    std::cout << "Hand : \n";
    for (size_t i = 0; i < 3; i++)
    {
        std::cout << "[" << i << "]";

        std::vector<const ResourceCard *> res = p.getRessources(i);

        for (size_t j = 0; j < res.size(); j++)
            std::cout << "[" << res[i] << "]";

        std::cout << "\n";
    }

    // Printing reserved cards
    std::cout << "Reserved : \n";
    for (size_t i = 0; i < 3; i++)
    {
        const ResourceCard *r = p.getReservedCards(i);
        if (r == nullptr)
            std::cout << "[ ]";
        else
            std::cout << "[" << r->toString() << "]";
    }
    std::cout << "\n";
}

void Splendor::TextualController::playTurn(size_t i)
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(i);

    // List every actions
}

#define WINNING_POINTS 15

bool Splendor::TextualController::hasWon(size_t i)
{
    Player &p = Game::getInstance().getPlayer(i);

    int points = p.getPoint();

    return points >= WINNING_POINTS;
}

void Splendor::TextualController::nobleVerification(size_t i)
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(i);

    std::vector<const NobleCard *> nobles = g.getBoard().getNobles();

    std::vector<const NobleCard *> compatibles = p.checkCompatibleNobles(nobles);

    if (compatibles.size() > 0)
    {
        // One noble
        if (compatibles.size() == 1)
        {
            // Remove from the board
            p.putNobleCard(g.getBoard().takeNobleCard(*compatibles[0]));
            return;
        }
        // Many nobles
        // Ask which noble to remove
        std::cout << "Many nobles wants to join your financial empire!\n"
                  << "Unfortunately, you have to pick one (and only one) from the following :\n";

        for (size_t i = 0; i < compatibles.size(); i++)
            std::cout << "[" << i << "]" << compatibles[i]->toString() << "\n";

        std::cout << "Pick a number (fast)\n";
        int j;

        std::cin >> j;

        while (j < 0 || j > compatibles.size())
        {
            std::cout << "This number doesn't seem appropriate... "
                      << "Please select a number between 0 and " << compatibles.size() << ".\n";
            std::cin >> j;
        }

        p.putNobleCard(g.getBoard().takeNobleCard(*compatibles[j]));
    }
}

void Splendor::TextualController::launch()
{
    initiateGame();

    while (true)
    {
        printGame();

        if (hasWon(actual_player))
            break;

        // Noble verification
        nobleVerification(actual_player);

        // Incrementation
        actual_player = (actual_player + 1) % Game::getInstance().getNbPlayer();
    }
}
