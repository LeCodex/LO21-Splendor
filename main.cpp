#include <QApplication>
#include "view/viewgame.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
//    Splendor::ResourceCard card(Splendor::Red, 3);
//    ViewResourceCard viewCard = ViewResourceCard(card);
//    Splendor::ResourceCard card(Splendor::Blue, 3);
//    ViewResourceCard viewCard;
//    viewCard.setCard(nullptr);
//    viewCard.show();

    ViewBoard board(*new Splendor::Board());
    board.show();
    return app.exec();
}
