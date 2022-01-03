#include "model.h"
#include "qtcontroller.h"

void Splendor::CitiesQtModel::initiateGame()
{
    // Create an instance of nb player
    Splendor::CitiesGame &g = Splendor::CitiesGame::createInstance(Splendor::QtController::getInstance().getNb());

    // Add the players
    for (size_t i = 0; i < Splendor::QtController::getInstance().getNb(); i++)
        g.addPlayer(Splendor::QtController::getInstance().getPlayerNames()[i]->text().toStdString(), Splendor::QtController::getInstance().getAi()[i]->checkState(), i);

    view = new ViewCitiesGame(&g, this);

    // Changer la couleur de fond
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor("#e6f2ff"));
    view ->setAutoFillBackground(true);
    view->setPalette(pal);
    view->show();

    // Après avoir initalisé le jeu, l'ajoute a la fenêtre
    setCentralWidget(view);

    show();
}
