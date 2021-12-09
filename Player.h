//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "Bank.h"
#include "ResourceCard.h"
#include "NobleCard.h"


namespace Splendor {
    class Player {
        Bank bank;
        const ResourceCard* ResourceCards[3];
        const NobleCard** NobleCards;
        const BaseCard* ReservedCards[3];
    public:
        Bank& getBank() {return bank;}

        int TotalToken() {
            int FinalAmount = 0;
            for (int i = 0; i<6; i++){
                FinalAmount += getBank().amount((Token)i);
            }
            return FinalAmount;
        }

        void PutReservedCard(const BaseCard card){};
        void TakeReservedCard(const BaseCard card){};
        void PutResourceCard(const ResourceCard* card){};
        void PutNobleCard(const NobleCard* card){};
        const BaseCard** getReservedCards() { return ReservedCards;};
    };
}