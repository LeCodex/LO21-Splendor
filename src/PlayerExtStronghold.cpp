#include "Player.h"

bool Splendor::PlayerExtStronghold::putStrongholds(){
    if (availableStrongholds > 3) {
        std::cout<<"Le joueur ne peux pas posséder plus de bastions";
        return false;
    }
    availableStrongholds++;
    return true;
}

bool Splendor::PlayerExtStronghold::takeStrongholds(){
    if (availableStrongholds < 0) {
        std::cout<<"Le joueur ne possède plus de bastions disponibles";
        return false;
    }
    availableStrongholds--;
    return true;
}
