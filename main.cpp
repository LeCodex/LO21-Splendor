#include <QApplication>
#include "view/viewgame.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    ViewCard card = ViewCard(new Splendor::BaseCard());
    card.show();

//    ViewBoard board(*new Splendor::Board());
//    board.show();
    return app.exec();
}
