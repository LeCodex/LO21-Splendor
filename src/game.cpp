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
        resources.loadXML(":/resources/resourcesxml");

        // Ressource deck generation :
        nobles.loadXML(":/nobles/noblesxml");

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
    delete[] players;
}

void Splendor::Game::addPlayer(std::string name, int index)
{
    if (players[index] != NULL)
        throw "Joueur déjà créé";
    std::cout << "Player \"" << name << "\" has been added to [" << index << "]\n";
    players[index] = new Player(name);
}

// Actions

bool Splendor::Game::canPlayerBuyCard(Splendor::Player &p, const Splendor::ResourceCard &card)
{
    //le cumulé des jetons du joueur (notamment le gold qui est un cas particulier), et de ses bonus doivent etre suffisant pour acheter la carte

    std::cout << card.toString() << "\n";

    int *bonus = p.getBonuses();
    int GoldAmount = p.getBank().amount(Gold);

    for (int i = 0; i < 5; i++)
    {
        int deficit = card.getCost((Token)i) - (bonus[i] + p.getBank().amount((Token)i));
        if (deficit > 0)
        {
            //Pour un jeton i, le cout sur la carte de ce jeton est supperieur aux bonus que possede le joueur sur ce jeton + le nombre de jetons qu'il possede de ce type
            if (deficit < GoldAmount) //Le joueur peut payer avec les jetons gold
                GoldAmount = GoldAmount - deficit;
            else //impossible de payer et arret
                return false;
        }
    }
    //Pour tous les types de jetons, ce que possède le joueur est supperieur ou egale à ce qui est demandé pour payer la carte
    return true;
}

int Splendor::Game::getRealCost(Splendor::Player &p, const Splendor::ResourceCard &card, Splendor::Token t)
{
    // Tableau de bonus du joueur
    int *bonus = p.getBonuses();

    // Retourne le prix de la carte pour ce token - la reduction que possede le joueur
    // 0 si négatif
    return (card.getCost(t) > bonus[int(t)]) ? card.getCost(t) - bonus[int(t)] : 0;
}

bool Splendor::Game::buyReservedCard(const Splendor::ResourceCard &card, Splendor::Player &p)
{

    // Etude de la condition de l'action
    if (!canPlayerBuyCard(p, card))
        return false;

    // Execution de l'action

    // Retrait des jetons au joueur
    for (int t = White; t != Gold; t++)
    {
        // On retire au joueur le prix à payer pour chaque jeton
        p.getBank().take((Token)t, getRealCost(p, card, (Token)t));
    }

    // Ajout de la carte au joueur
    p.putResourceCard(card);

    // Ajoute à la bank le prix que le joueur paye
    for (int t = White; t != Gold; t++)
    {
        board.getBank().put((Token)t, getRealCost(p, card, (Token)t));
    }

    // Retrait de la carte du tableau de cartes reservées du joueur
    p.takeReservedCard(card);

    return true;
}

bool Splendor::Game::buyBoardCard(const Splendor::ResourceCard &card, Splendor::Player &p)
{ ///Pas finit (cf mise a jour du plateau)

    // Etude de la condition de l'action
    if (!canPlayerBuyCard(p, card))
        return false;

    // Execution de l'action

    // Retrait des jetons au joueur
    for (int t = White ; t != Gold; t++)
    {
        p.getBank().take((Token)t, getRealCost(p, card, (Token)t));
        //On retire au joueur le prix de la carte pour chaque jeton
    }

    // Ajout de la carte au joueur
    p.putResourceCard(card);

    // Ajoute à la bank le prix que le joueur paye
    for (int t = White; t != Gold; t++)
    {
        board.getBank().put((Token)t, getRealCost(p, card, (Token)t));
    }

    // Retrait de la carte du plateau
    board.takeCenterCard(card);

    // Rajout des cartes au centre
    board.replenishCenterCards();

    return true;
}

bool Splendor::Game::reserveCenterCard(const Splendor::ResourceCard &card, Splendor::Player &p)
{
    // Etude de la condition de l'action
    // Chaque joueur peut avoir au max 3 cartes reservées
    if (p.getReservedCards(0) != nullptr && p.getReservedCards(1) != nullptr && p.getReservedCards(2) != nullptr)
        return false;

    // Retrait de la carte du plateau
    board.takeCenterCard(card);

    //Pioche d'une nouvelle carte de bon niveau
    board.replenishCenterCards();

    ///Ajout de la carte choisis au tableau de cartes reservées du joueur
    p.putReservedCard(card);

    ///Ajout d'un jeton or au joueur apres chaque reservation
    p.getBank().put(Gold, 1);

    return true;
}

bool Splendor::Game::reserveDrawCard(size_t i, Splendor::Player &p)
{
    // Etude de la condition de l'action
    // Chaque joueur peut avoir au max 3 cartes reservées
    if (p.getReservedCards(0) != nullptr && p.getReservedCards(1) != nullptr && p.getReservedCards(2) != nullptr)
        return false;

    // Retrait de la carte du plateau
    if (board.getDrawPile(i).empty())
        return false;
    const ResourceCard &card = board.getDrawPile(i).draw();

    // Ajout de la carte choisis au tableau de cartes reservées du joueur
    p.putReservedCard(card);

    // Ajout d'un jeton or au joueur apres chaque reservation
    p.getBank().put(Gold, 1);

    return true;
}

bool Splendor::Game::takeTwoIdenticalToken(Splendor::Token color, Splendor::Player &p)
{

    // Etude de la condition de l'action

    // Si la banque a moins 4 jetons d'une couleur
    if (board.getBank().amount(color) < 4)
        return false;

    // Ajout des 2 jetons à la banque du joueur
    p.getBank().put(color, 2);

    //Retrait des 2 jetons à la banque du plateau
    board.getBank().take(color, 2);

    // DO SOMETHING HERE
    if (p.TotalToken() > 10)
        ;

    return true;
}

bool Splendor::Game::takeThreeDifferentToken(Splendor::Token color1, Splendor::Token color2, Splendor::Token color3, Splendor::Player &p)
{

    // Etude de la condition de l'action
    // La banque doit avoir assez de jeton
    if (!((board.getBank().amount(color1) >= 1) && (board.getBank().amount(color2) >= 1) && (board.getBank().amount(color3) >= 1)))
        return false;

    // Mise à jour des jetons du joueur
    p.getBank().put(color1, 1);
    p.getBank().put(color2, 1);
    p.getBank().put(color3, 1);

    ///Mise à jour de la banque
    board.getBank().take(color1, 1);
    board.getBank().take(color2, 1);
    board.getBank().take(color3, 1);

    // DO SOMETHING HERE
    if (p.TotalToken() > 10)
        ;

    return true;
}

void Splendor::Game::playIA(Splendor::Player &p, int level){

    if (level == 1) {
    ///Stratégie de l'IA moyenne:
    //1 ) Si elle peut acheter une de ses cartes reservées elle l'achete
    //2 ) Si non si elle peut acheter une des cartes du plateau elle l'achete
    //3 ) Si non elle prend de maniere aléatoire soit 2 token identique soit 3 diffèrents
              //Si elle ne parvint pas à faire l'action retenue on essaye de faire l'autre
    //4 ) Si elle a trop de jetons et qu'elle n'a pas pu en prendre elle reserve une carte


        ///1 )Recherche de la premiere carte reservée qu'elle peut acheter et achat eventuel
        for(int i = 0; i < 3; i ++){
            if (buyReservedCard(board.getCard(i))) return; //L'IA a acheté sa iéme carte reservée
            }


        ///2 )Recherche de la premiere carte qu'elle peut acheter sur le plateau et achat eventuel
        for(int i = 0; i < 3; i ++){
            for(int j = 0; j < 4; j ++){
                if (buyBoardCard(board.getCard(i,j))) return; //L'IA a acheté la carte du plateau d'indice i,j
        }}


        ///3 )Recherche des jetons qu'elle peut obtenir et prise eventuelle

        //Selection de l'action de manière aléatoire
        std::srand(std::time(nullptr));
        int choice = std::rand() % 2;
        if( choice == 1 ){     //Action retenue : Pioche de 3 token diffèrents
            for (int t1 = White; t1 != Gold; t1++){
                for (int t2 = Blue ; t2 != Gold; t2++){
                    for (int t3 = Green ; t3 != Gold; t3++){
                        if (takeThreeDifferentToken((Token)t1,(Token)t2,(Token)t3,p)) return // l'IA a pris ses trois jetons
                    }
                }
            }
            //Si le joueur n'a pas pu prendre 3 jetons differents on essaye d'en prendre 2
            for (int t = White; t != Gold; t++){
                if (takeTwoIdenticalToken((Token)t,p)) return // l'IA a pris ses 2 jetons
            }

        }else {             //Action retenue :Pioche de 2 token identiques
            for (int t = White; t != Gold; t++){
                 if (takeTwoIdenticalToken((Token)t,p)) return // l'IA a pris ses 2 jetons
                    }
            //Si le joueur n'a pas pu prendre 2 jetons identiques on essaye d'en prendre 3 diffèrents
            for (int t1 = White; t1 != Gold; t1++){
                for (int t2 = Blue ; t2 != Gold; t2++){
                    for (int t3 = Green ; t3 != Gold; t3++){
                        if (takeThreeDifferentToken((Token)t1,(Token)t2,(Token)t3,p)) return // l'IA a pris ses trois jetons
                    }
                }
            }
        }


        ///4 )Recherche des cartes qu'elle peut reserver et reservation

        //Tentative de reservation d'une carte venant d'une des trois pioches
        for (int i =0; i != 3; i++){
            if (reserveDrawCard(i,p)) return; // L'IA a reservé une carte de la pioche i
        }

        //Si toutes les pioches sont vide reservation de la premiere carte du plateau
        reserveCenterCard(board.getCard(0,0),p);

    }

}
