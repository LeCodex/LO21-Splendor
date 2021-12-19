//
// Created by Cléa Bordeau on 01/12/2021.
//
#include "Splendor.h"
#include "action.h"

///Reste a faire sur ce fichier : Tester

namespace Splendor
{
    class Take_3_diff_Token : public Action
    {
    private:
        Token color1;
        Token color2;
        Token color3;

        //methodes appelées pour l'execution
        void PlayerTokenUpdate(Player &p) const
        {
            p.getBank().put(color1, 2);
            p.getBank().put(color2, 2);
            p.getBank().put(color3, 2);
        };

        void BankUpdate(Board &b) const
        {
            b.getBank().take(color1, 1);
            b.getBank().take(color2, 1);
            b.getBank().take(color3, 1);
        };

    public:
        Take_3_diff_Token(Token c1, Token c2, Token c3) : color1(c1), color2(c2), color3(c3){};

        bool condition(Board &b, Player &p) const override;
        //la banque doit avoir assez de jeton
        //et un joueur ne doit jamais avoir plus de 10 jetons à la fin de son tour

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