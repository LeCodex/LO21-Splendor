#include "viewcitiesboard.h"
#include "viewcitiescard.h"
#include "../qtcontroller.h"

ViewCitiesBoard::ViewCitiesBoard(Splendor::Board& b, QWidget* parent) : ViewBoard(b, parent) {}

void ViewCitiesBoard::createNobles() {
    nobleCardsLayout = new QHBoxLayout();
    auto nobles = board->getNobles();
    for (size_t i = 0; i < nobles.size(); i++) {
        ViewCitiesCard* v = new ViewCitiesCard();
        QObject::connect(v, &ViewCitiesCard::cardClicked, [v](){
            Splendor::QtController::getInstance().getModel().chooseNoble((Splendor::NobleCard*)v->getCard());
        });
        viewNobleCards.push_back(v);
        viewNobleCards.back()->setCard(nobles[i]);
        nobleCardsLayout->addWidget(viewNobleCards.back());
    }
}
