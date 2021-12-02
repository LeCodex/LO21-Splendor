#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
private:
    const string name;
    Bank bank;
    const RessourceCard** cards[3];
    const NobleCard** nobles;
public:
    Player(string s, int n) : name(s){};
    ~Player();
    Action play(vector<Action> actions);
    Bank getBank() {return bank;}
    string getName() {return name;}
    RessourceCard getRessourceCard(int i) {return cards[i]};
    int* getBonuses();
    int getPoint();
    };
