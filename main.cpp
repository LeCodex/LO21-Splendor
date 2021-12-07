#include <iostream>
#include "splendor.h"
#include "NobleCard.h"
int main() {
    std::cout << "Splendor!" << std::endl;
    using namespace Splendor;
    int tb[5]= {0,1,1,3,0};
    NobleCard C1( tb ,5);
    int FinalAmount = 0;
    //FinalAmount += C1.getCost(1); //Pb
    return 0;
}
