#include"ResourceCard.h"
#include"Player.h"

bool occupy(PlayerExtStronghold& player){
    if (occupant!=player && occupant!=nil) {
        std::cout<<"La carte est déja occupée";
        return false;
    } 
    else
    {
        occupant=player;
        if (nbStronghold>3) {
            std::cout<<"Nombre de bastion max atteint";
            return false;
        }
        if (player.getAvailableStrongholds()<1) {
            std::cout<<"Le joueur ne possède plus de bastion disponible"
            return false;
        }
    }
}

bool occupy(PlayerExtStronghold& player){
    if (occupant!=player && occupant!=nil) {
        std::cout<<"La carte est déja occupée";
        return false;
    } 
    else
    {
        occupant=player;
        if (nbStronghold>3) {
            std::cout<<"Nombre de bastion max atteint";
            return false;
        }
        if (player.getAvailableStrongholds()<1) {
            std::cout<<"Le joueur ne possède plus de bastion disponible"
            return false;
        }
    }
}

void conquest (){
    nbStronghold=0;
    occupant=nil;
}