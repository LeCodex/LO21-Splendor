#include"ResourceCard.h"
#include"Player.h"

bool Splendor::ResourceCardStronghold::occupy(Splendor::PlayerExtStronghold& player){
    if (occupant && occupant != &player) {
        std::cout << "La carte est déja occupée";
        return false;
    } 
    else
    {
        if (nbStronghold>3) {
            std::cout<<"Nombre de bastion max atteint";
            return false;
        }
        if (player.getAvailableStrongholds()<1) {
            std::cout<<"Le joueur ne possède plus de bastion disponible";
            return false;
        }
    }
    occupant = &player;
    return true;
}

bool Splendor::ResourceCardStronghold::remove(Splendor::PlayerExtStronghold& player){
    if(!occupant){
        std::cout << "La carte est occupée par aucun jouer";
        return false;
    }
    if (occupant != &player) {
        std::cout << "La carte est occupée par un joueur différent";
        return false;
    }
    occupant = nullptr;
    return true;
}


void Splendor::ResourceCardStronghold::conquest(){
    nbStronghold = 0;
    occupant = nullptr;
}
