//
// Created by Cléa Bordeau on 24/12/2021.
//

#include "Controller.h"
bool Splendor::Controller::BuyReservedCard(BaseCard card, Board& b, Player& p){

    ///Etude de la condition de l'action
    if (conditionBuyCard(b,p,card) == 0) return false;


    ///Execution de l'actions
    else{
        ///Retrait des jetons au joueur
        for (int t=Red; t!=Gold; t++) {
            p.getBank().take((Token)t,real_cost(p,card,(Token)t));
            //On retire au joueur le prix à payer pour chaque jeton
        }

        ///Ajout de la carte au joueur
        p.PutResourceCard(card);

        ///Ajoute à la bank le prix que le joueur paye
        for (int t=Red; t!=Gold; t++) {
            b.getBank().put((Token)t, real_cost(p,card,(Token)t));
        }

        /////Retrait de la carte du tableau de cartes reservées du joueur
        p.TakeReservedCard(card);

    }
    return true;
}




bool Splendor::Controller::BuyBoardCard(BaseCard card, Board& b, Player& p){ ///Pas finit (cf mise a jour du plateau)

    ///Etude de la condition de l'action
    if (conditionBuyCard(b,p,card) == 0) return false;


    ///Execution de l'action
    else{

        ///Retrait des jetons au joueur
        for (int t=Red; t!=Gold; t++) {
            p.getBank().take((Token)t,real_cost(p,card,(Token)t));
            //On retire au joueur le prix de la carte pour chaque jeton
        }

        ///Ajout de la carte au joueur
        p.PutResourceCard(card);

        ///Ajoute à la bank le prix que le joueur paye
        for (int t=Red; t!=Gold; t++) {
            b.getBank().put((Token)t,real_cost(p,card,(Token)t));
        }

        ///Mise a jour du plateau (reste à faire)
        //Retrait de la carte du plateau
        //Pioche d'une nouvelle carte de bon niveau
        //Ajout de la carte piochée au plateau

    }
    return true;

}



bool Splendor::Controller::ReservCard(BaseCard card, Board& b, Player& p){ ///Pas finit (cf mise a jour du plateau)

    ///Etude de la condition de l'action
    //Chaque joueur peu avoir au max 3 cartes reservées

    bool condition;
    int nb = 0;
    //Calcul du nombre de cartes déja reservées pour le joueur
    for (auto i=0; i<=sizeof(p.getReservedCards()); i++){
        if(p.getReservedCards()[i] != nullptr) ++nb;
    }
    condition = (nb<=2);
    if (condition == 0) return false;


    ///Execution de l'action
    else{
        ///Mise a jour du plateau (reste à faire)
        //Retrait de la carte du plateau
        //Pioche d'une nouvelle carte de bon niveau
        //Ajout de la carte piochée au plateau

        ///Ajout de la carte choisis au tableau de cartes reservées du joueur
        p.PutReservedCard(card);

        ///Ajout d'un jeton or au joueur apres chaque reservation
        p.getBank().put(Gold,1);

    }
    return true;
}

bool Splendor::Controller::Take_2_identical_Token(Token color, Board& b, Player& p){

    ///Etude de la condition de l'action
    //La banque doit avoir les jetons disponible
    //Le joueur doit avoir moins de 10 jetons à la fin de son tour

    bool condition;
    int FinalAmount = p.TotalToken() + 3;
    FinalAmount += 2;
    condition = ((b.getBank().amount(color)>=2) && (FinalAmount <= 10));
    if (condition == 0) return false;


    ///Execution de l'action
    else {
        p.getBank().put(color, 2); //Ajout des 2 jetons à la banque du joueur
        b.getBank().take(color, 2); //Retrait des 2 jetons à la banque du plateau
    }
    return true;
}

bool Splendor::Controller::Take_3_diff_Token(Token color1, Token color2, Token color3, Board& b, Player& p){

    ///Etude de la condition de l'action
    //La banque doit avoir assez de jeton
    //LE joueur ne doit pas avoir plus de 10 jetons à la fin de son tour

    bool condition;
    int FinalAmount = p.TotalToken() + 3;
    condition = ((b.getBank().amount(color1)>=1) && (b.getBank().amount(color2)>=1) && (b.getBank().amount(color3)>=1)
            && (FinalAmount <=10));
    if (condition == 0) return false;


   ///Execution de l'action
    else {
        ///Mise à jour des jetons du joueur
        p.getBank().put(color1,2);
        p.getBank().put(color2,2);
        p.getBank().put(color3,2);

        ///Mise à jour de la banque
        b.getBank().take(color1,1);
        b.getBank().take(color2,1);
        b.getBank().take(color3,1);
    }
    return true;

}




///Utilitaires pour les fonctions actions BuyCard:

int Splendor::Controller:: real_cost(Player& p,BaseCard card, Token t) {
    int* bonus = p.getBonuses(); //tableau de bonus du joueur
    return card.getCost(t) - bonus[int(t)]; //retourne le prix de la carte pour ce token - la reduction que possede le joueur
}

bool Splendor::Controller::conditionBuyCard(Board &b, Player &p, BaseCard card) {
    //le cumulé des jetons du joueur (notamment le gold qui est un cas particulier), et de ses bonus doivent etre suffisant pour acheter la carte

    int* bonus = p.getBonuses();
    int GoldAmount = p.getBank().amount(Gold);

    for(int i=0; i <5; i++){
        int deficit = card.getCost((Token)i) - (bonus[i]+ p.getBank().amount((Token)i));
        if( deficit > 0 ) {
            //Pour un jeton i, le cout sur la carte de ce jeton est supperieur aux bonus que possede le joueur sur ce jeton + le nombre de jetons qu'il possede de ce type
            if ( deficit < GoldAmount ) //Le joueur peut payer avec les jetons gold
                GoldAmount = GoldAmount-deficit;
            else //impossible de payer et arret
                return false;
        }
    }
    //Pour tous les types de jetons, ce que possède le joueur est supperieur ou egale à ce qui est demandé pour payer la carte
    return true;
}
