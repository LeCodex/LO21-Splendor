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

    size_t length = 6;
    string actionsName[length] = {"Prendre 3 jetons pierre précieuse de couleur différente",
                                  "Prendre 2 jetons pierre précieuse de la même couleur",
                                  "Réserver 1 carte développement depuis une pioche et prendre 1 or (joker)",
                                  "Réserver 1 carte développement depuis le centre et prendre 1 or (joker)",
                                  "Acheter  1  carte  développement  face  visible  au  centre  de  la  table",
                                  "Acheter  1  carte  développement  préalablement reservée"};

    bool (Splendor::TextualController::*(actions[]))() = {&Splendor::TextualController::takeThreeDifferentToken,
                                                          &Splendor::TextualController::takeTwoIdenticalToken,
                                                          &Splendor::TextualController::reserveDrawCard,
                                                          &Splendor::TextualController::reserveCenterCard,
                                                          &Splendor::TextualController::buyBoardCard,
                                                          &Splendor::TextualController::buyReservedCard};

    // On boucle a l'infini tant qu'aucune action valide n'a été effectuée
    do
    { // List every actions
        std::cout << "Joueur " << p.getName() << ", choisissez une action entre 0 et " << (length - 1) << " : \n";
        for (size_t i = 0; i < length; i++)
            std::cout << "[" << i << "] " << actionsName[i] << "\n";

        int n;
        std::cin >> n;

        while (n < 0 || n > length)
        {
            std::cout << "Erreur, chiffre non pris en charge... Réessayez en choisissant une action entre 0 et " << (length - 1) << "\n";
            std::cin >> n;
        }

        if ((*this.*actions[n])())
            break;

    } while (true);
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

        playTurn(actual_player);

        // Overflow of token verification
        // TODO...

        // Noble verification
        nobleVerification(actual_player);

        // End game verification
        if (hasWon(actual_player))
            break;

        // Incrementation
        actual_player = (actual_player + 1) % Game::getInstance().getNbPlayer();
    }
}

// Actions

bool Splendor::TextualController::buyReservedCard()
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(actual_player);

    const ResourceCard *cards[3] = {p.getReservedCards(0),
                                    p.getReservedCards(1),
                                    p.getReservedCards(2)};

    // Cas ou aucune carte n'est reservée
    if (cards[0] == nullptr && cards[1] == nullptr && cards[2] == nullptr)
    {
        std::cout << "Aucune carte reservée...\n";
        return false;
    }

    std::cout << "Choissisez une carte entre 0 et 3\n";

    int n;
    std::cin >> n;

    while (n < 0 || n > 3)
    {
        std::cout << "Erreur, chiffre non pris en charge... Réessayez en choisissant une carte entre 0 et 3";
    }

    if (g.buyReservedCard(*cards[n], p))
    {
        std::cout << "Achat de la carte reservée effectué avec succès!\n";
        return true;
    }

    std::cout << "Impossible d'acheter la carte reservée selectionnée...\n";
    return false;
}

bool Splendor::TextualController::buyBoardCard()
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(actual_player);
    Board &b = g.getBoard();
    
    printGame();
    std::cout<<"Veuillez choisir la carte que vous voulez acheter :\n";
    std::cout<<"Ligne ? :\n";
    int i;
    std::cin>>i;
    while(i<0 || i>3)
    {
        std::cout<<"Erreur : numéro de ligne invalide";
        std::cin>>i;
    }

    std::cout<<"Colonne ? :\n";
    int j;
    std::cin>>j; 
    while(j<0 || j>4)
    {
        std::cout<<"Erreur : numéro de colonne invalide";
        std::cin>>j;
    }
    //on récup la j eme carte du i eme paquet
    Splendor::ResourceCard const &card = b.getCard(i,j);

    if (g.buyBoardCard(card,p))
    {
        std::cout << "L'achat de la carte a été effectué avec succès!\n";
        return true;
    }

    std::cout << "Impossible d'acheter la carte selectionnée...\n";
    return false;
}

bool Splendor::TextualController::reserveCenterCard()
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(actual_player);
    Board &b = g.getBoard();
    
    printGame();
    std::cout<<"Veuillez choisir la carte que vous voulez réserver :\n";
    std::cout<<"Ligne ? :\n";
    int i;
    std::cin>>i;
    while(i<0 || i>3)
    {
        std::cout<<"Erreur : numéro de ligne invalide";
        std::cin>>i;
    }

    std::cout<<"Colonne ? :\n";
    int j;
    std::cin>>j; 
    while(j<0 || j>4)
    {
        std::cout<<"Erreur : numéro de colonne invalide";
        std::cin>>j;
    }
    //on récup la j eme carte du i eme paquet
    Splendor::ResourceCard const &card = b.getCard(i,j);

    if (g.reserveCenterCard(card,p))
    {
        std::cout << "La réservation de la carte effectué avec succès!\n";
        return true;
    }

    std::cout << "Impossible de réserver la carte selectionnée...\n";
    return false;
}

bool Splendor::TextualController::reserveDrawCard()
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(actual_player);
    Board &b = g.getBoard();

    std::cout<<"De quelle pile voulez-vous réserver une carte ?\n";
    std::cout<<"[1 2 ou 3]\n";
    size_t i;
    std::cin>>i;
    while(i<1 || i>3)
    {
        std::cout<<"Saise invalide, réessayez";
        std::cin>>i;
    }

    if (g.reserveDrawCard(i,p))
    {
        std::cout << "La réservation de la carte a été effectuée avec succès!\n";
        return true;
    }

    std::cout << "Impossible de réserver la carte selectionnée...\n";
    return false;
}
bool Splendor::TextualController::takeTwoIdenticalToken()
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(actual_player);
    std::cout<<"Quelle couleur voulez-vous piocher ?\n";
    std::cout<<"1- Bleu\n";
    std::cout<<"2- Rouge\n";
    std::cout<<"3- Vert\n";
    std::cout<<"4- Blanc\n";
    std::cout<<"5- Noir\n";
    size_t i;
    std::cin>>i;
    while(i<1 || i>5)
    {
        std::cout<<"Saisie invalide : veuillez reessayer";
        std::cin>>i;
    }

    if (g.takeTwoIdenticalToken((Token) i,p))
    {
        std::cout << "Les deux jetons ont bien été pioché!\n";
        return true;
    }

    std::cout << "Pioche échouée...\n";
    return false;
}
bool Splendor::TextualController::takeThreeDifferentToken()
{
    Game &g = Game::getInstance();
    Player &p = g.getPlayer(actual_player);

    int choice[3];

    for (size_t loop=0;loop<3;loop++)
    {
        std::cout<<"Quelle couleur voulez-vous piocher ? ("<<loop+1<<"/3)\n";
        std::cout<<"1- Bleu\n";
        std::cout<<"2- Rouge\n";
        std::cout<<"3- Vert\n";
        std::cout<<"4- Blanc\n";
        std::cout<<"5- Noir\n";
        size_t i;
        std::cin>>i;
        while(i<1 || i>5)
        {
            std::cout<<"Saisie invalide : veuillez reessayer";
            std::cin>>i;
        }
        choice[loop]=i;
    }


    if (g.takeThreeDifferentToken((Token) choice[0],(Token) choice[1],(Token) choice[2],p))
    {
        std::cout << "Les deux jetons ont bien été pioché!\n";  
        return true;
    }

    std::cout << "Pioche échouée...\n";
    return false;
}
