//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "Splendor.h"
#include "action.h"

///Reste a faire sur ce fichier : Tester

namespace Splendor
{
    class Take_2_identical_Token : public Action
    {
    private:
        Token color;

        //methodes appelées pour l'execution
        void BankUpdate(Board &b) const { b.getBank().take(color, 2); };

        void PlayerTokenUpdate(Player &p) const { p.getBank().put(color, 2); };

    public:
        Take_2_identical_Token(Token c) : color(c){};

        bool condition(Board &b, Player &p) const override;

        void executer(Board &b, Player &p) override
        {
            if (condition(b, p))
            {
                PlayerTokenUpdate(p);
                BankUpdate(b);
            }
        };
    };
}