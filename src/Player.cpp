#include "Player.h"
#include "ResourceCard.h"
#include <vector>

//getPoint calcule le nombre de points d'un joueur en additionnant les prestiges des cartes ressources
int Splendor::Player::getScore() const
{
    int result = 0;

    for (size_t i = 0; i < 3; i++)
    {
        for (auto &tmp : ressource[i])
        {
            result += tmp->getPrestige();
        }
    }

    for (auto noble : nobles)
    {
        result += noble->getPrestige();
    }

    return result;
}

//getBonuses recupere tous les discounts des cartesRessources
int* Splendor::Player::getBonuses() const
{
    int *bonuses = new int[5];
    for (size_t i = 0; i < 5; i++)
        bonuses[i] = 0;

    for (size_t i = 0; i < 3; i++)
    {
        for (auto &tmp : ressource[i])
        {
            bonuses[tmp->getResource()] += 1;
        }
    }
    return bonuses;
}

void Splendor::Player::putReservedCard(const Splendor::ResourceCard &card)
{
    for (size_t i = 0; i < 3; i++)
        if (ReservedCards[i] == nullptr)
        {
            ReservedCards[i] = &card;
            return;
        }
    throw "No space available\n";
}

const Splendor::ResourceCard &Splendor::Player::takeReservedCard(size_t i)
{
    const ResourceCard &card = *ReservedCards[i];
    ReservedCards[i] = nullptr;
    return card;
}
const Splendor::ResourceCard &Splendor::Player::takeReservedCard(const Splendor::ResourceCard &card)
{
    for (size_t i = 0; i < 3; i++)
        if (&card == ReservedCards[i])
            return takeReservedCard(i);
    throw "Error, this card isnt reserved by this player.\n";
}

void Splendor::Player::putResourceCard(const Splendor::ResourceCard &card)
{
    int niveau = card.getLevel();
    ressource[niveau].push_back(&card);
}

void Splendor::Player::putNobleCard(const Splendor::NobleCard &card)
{
    nobles.push_back(&card);
}
