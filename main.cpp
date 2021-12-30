#include <QApplication>
#include "src/view/viewgame.h"
#include <QDebug>
#include "src/controller.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
//    Splendor::ResourceCard card(Splendor::Blue, 3);
//    int cost[5] = {1, 2, 3, 4, 5};
//    card.setCost(cost);
//    ViewResourceCard viewCard;
//    viewCard.setCard(&card);
//    viewCard.show();

//    ViewCost* costs[5];
//    for (size_t i = 0; i < 5; i++) costs[i] = new ViewCost();
//    QVBoxLayout b;
//    for (auto c : costs) b.addWidget(c);
//    QWidget w;
//    w.setLayout(&b);
//    w.show();

//    ViewBoard board(*new Splendor::Board());
//    board.show();

//    ViewPlayer player;
//    player.show();

/*    srand(time(NULL));
    Splendor::Game& g = Splendor::Game::createInstance(4);

    ViewGame game(&g);

    game.showNormal(); */

    Splendor::QtController &controller = Splendor::QtController::getInstance();

    controller.launch();

    return app.exec();
}
