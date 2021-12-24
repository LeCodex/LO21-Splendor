#include <QApplication>
#include "view/viewgame.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
//    Splendor::ResourceCard card(Splendor::Red, 3);
//    ViewResourceCard viewCard = ViewResourceCard(card);
    Splendor::ResourceCard card(Splendor::Blue, 3);
    int cost[5] = {1, 1, 1, 1, 1};
    card.setCost(cost);
    ViewResourceCard viewCard;
    viewCard.setCard(&card);
    viewCard.show();

//    ViewBoard board(*new Splendor::Board());
//    board.show();

//    ViewPlayer player;
//    player.show();
    return app.exec();
}
