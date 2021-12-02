//
// Created by thoma on 02/12/2021.
//

#ifndef PROJET_RULES_H
#define PROJET_RULES_H

#endif //PROJET_RULES_H

class Rules {
private:
    //int nbOfRules;
public:
    isWinning(player& p) {if (p->points>=15) return TRUE;}
    /*
    canBeBought(player& p, int costs[5]){
        bool check=TRUE; int diff;
        for (size_t i=0;i<5:i++){
            if (p.nbToken[i]<cost[i]) diff=cost[i]-p.nbToken[i];
        }
        if (check>p.nbToken[5]) check=FALSE;
        return check;
    }
     */
    nobleMax(player& p);
};