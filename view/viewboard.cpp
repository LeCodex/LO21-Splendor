#include "viewboard.h"

ViewBoard::ViewBoard(Splendor::Board& b, QWidget *parent) : QWidget(parent), board(&b)
{
    centralBankLayout = new QVBoxLayout();

    // Central bank
    for (int i = 0; i < 6; i++) {
        viewTokens[i] = new ViewToken((Splendor::Token)i);
        viewTokens[i]->setAmount(8);
        centralBankLayout->addWidget(viewTokens[i]);
    }

    setLayout(centralBankLayout);
}
