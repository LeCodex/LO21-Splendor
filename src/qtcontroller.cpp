#include <QWidget>
#include "controller.h"
#include <QMessageBox>

Splendor::QtController::QtController(QWidget* parent): QWidget(parent){
    initiateGame();

    // Après avoir initalisé le jeu, l'ajoute a la fenêtre
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(view);

    setLayout(layout);

    showNormal();
}

void Splendor::QtController::initiateGame(){
    // Create a pop up to ask how many players
    // what type of player for each (and username)*

    // TODO...
    // Modify message box to ask for settings
    QMessageBox msgBox;
    msgBox.setText("text.str().c_str()");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *speed = msgBox.addButton("Speed optimization", QMessageBox::AcceptRole);
    QPushButton *memory = msgBox.addButton("Memory optimization", QMessageBox::AcceptRole);
    QPushButton *close = msgBox.addButton("Close", QMessageBox::RejectRole);
    msgBox.setDefaultButton(speed);
    msgBox.exec();

    Splendor::Game& g = Splendor::Game::createInstance(4);

    view = new ViewGame(&g);
}
void Splendor::QtController::playTurn(size_t){}
// Verify if the specified player can receive a noble
void Splendor::QtController::nobleVerification(size_t){}
// Verifiy if the player is too rich
void Splendor::QtController::overflowVerification(size_t){}
