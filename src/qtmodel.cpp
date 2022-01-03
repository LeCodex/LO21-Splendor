#include "model.h"

Splendor::QtModel::QtModel(QWidget *parent) : QMainWindow(parent) {}

void Splendor::QtModel::initiateGame()
{
    // Create a pop up to ask how many players
    // what type of player for each (and username)*

    // Modify message box to ask for settings
    QDialog dialog;

    dialog.setWindowTitle("Splendor");

    QFormLayout form(&dialog);

    form.addRow(new QLabel("# Réglages de la partie"));

    QString label = QString("Combien de joueur souhaitez vous?");
    QSpinBox *nbJoueurs = new QSpinBox;
    nbJoueurs->setRange(2, 4);
    nbJoueurs->setSingleStep(1);
    nbJoueurs->setValue(2);

    form.addRow(label, nbJoueurs);

    QWidget *widgets[4];
    QLineEdit *playerNames[4];
    QCheckBox *AI[4];

    // First we create the four widgets
    for (size_t i = 0; i < 4; i++)
    {
        QWidget *widget = new QWidget;
        QHBoxLayout *line = new QHBoxLayout();
        QLabel *player = new QLabel(QString("Joueur #%1").arg(i));
        QLineEdit *playerInput = new QLineEdit;
        playerInput->setText(QString("Joueur_%1").arg(i));
        QCheckBox *isAI = new QCheckBox("IA");

        line->addWidget(player);
        line->addWidget(playerInput);
        line->addWidget(isAI);

        widget->setLayout(line);

        widgets[i] = widget;
        playerNames[i] = playerInput;
        AI[i] = isAI;

        form.addRow(widgets[i]);
    }

    // Function to enable them or not
    auto players = [&widgets, &dialog](int size)
    {
        for (size_t i = 0; i < 4; i++)
        {
            widgets[i]->setVisible(i < size);
            dialog.adjustSize();
        }
    };

    // When we modify the slot value, the number of input player is decreased
    QObject::connect(nbJoueurs, &QSpinBox::valueChanged, [&nbJoueurs, &players]()
                     { players(nbJoueurs->value()); });

    players(2);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

    dialog.exec();

    dialog.close();

    size_t nb = std::stoi(nbJoueurs->text().toStdString());

    // Create an instance of nb player
    Splendor::Game &g = Splendor::Game::createInstance(nb);

    // Add the players
    for (size_t i = 0; i < nb; i++)
        g.addPlayer(playerNames[i]->text().toStdString(), AI[i]->checkState(), i);

    view = new ViewGame(&g, this);

    // Après avoir initalisé le jeu, l'ajoute a la fenêtre
    setCentralWidget(view);

    show();
}

bool actionPerformed = false;

void Splendor::QtModel::playTurn(size_t)
{
    view->update();
    view->getInfo()->setText("Cliquez sur les jetons ou cartes du plateau pour effectuer des actions");

    qInfo() << "Waiting for player action...";
    view->setActivePlayer(currentPlayer);
    tokenSelection.clear();
    phase = Phase::Play;

    Game& game = getGameInstance();
    Splendor::Player& player = game.getPlayer(currentPlayer);

    if (player.isAI()) {
        game.playAI(player, 1);
    } else {
        // While no action has been performed, just wait for one
        while (!actionPerformed && !this->stopped) {
            QApplication::processEvents();
        }
    }

    if(this->stopped) return;

    // Hiding the hand in case it isn't
    view->getPlayers()[currentPlayer]->getHand()->hide();

    qInfo() << "Action performed!";

    actionPerformed = false;
}

// Verify if the specified player can receive a noble
void Splendor::QtModel::nobleVerification(size_t) {
    qInfo() << "Noble verification";
    view->update();

    Splendor::Game& game = getGameInstance();
    Splendor::Player& player = game.getPlayer(currentPlayer);

    phase = Phase::Nobles;

    vector<const Splendor::NobleCard*> nobles;
    for (auto noble : game.getBoard().getNobles()) {
        if (noble->canBeTakenBy(player)) nobles.push_back(noble);
    }
    // qInfo() << nobles.size();

    if (nobles.size() == 1) {
        game.chooseNoble(*nobles[0], player);
        promptError("Vous avez reçu un noble!");
    } else if (nobles.size() > 1) {
        // Disable nobles that can't be picked
        for (auto viewNoble : view->getBoard()->getNobleCards()) {
            viewNoble->setDisabled(true);

            for (auto noble : nobles) {
                if (noble == viewNoble->getCard()) {
                    viewNoble->setDisabled(false);
                    break;
                }
            }
        }

        if (player.isAI()) {
            game.chooseNoble(*nobles[0], player);
            promptError("Vous avez reçu un noble!");
        } else {
            view->getInfo()->setText("Choississez un noble à prendre");
            promptError("Veuillez choisir un noble à recevoir");

            // Wait for the player to choose a noble
            while (!actionPerformed && !this->stopped){
                QApplication::processEvents();
            }
        }
    } // Else do nothing

    for (auto viewNoble : view->getBoard()->getNobleCards()) {
        viewNoble->setDisabled(false);
    }

    actionPerformed = false;
}

// Verifiy if the player is too rich
void Splendor::QtModel::overflowVerification(size_t) {
    qInfo() << "Overflow verification";

    Splendor::Game& game = getGameInstance();
    Splendor::Player& player = game.getPlayer(currentPlayer);

    phase = Phase::Overflow;

    if (player.TotalToken() > 10 && !player.isAI()) {
        promptError("Veuillez choisir des jetons à rendre");
        view->getInfo()->setText("Vous avez trop de jetons! Choississez en à rendre");
    }

    while (player.TotalToken() > 10) {
        if (player.isAI()) {
            game.returnTokenAI(player);
        } else {
            view->update();

            // Wait for the player to remove tokens
            while (!actionPerformed && !this->stopped){
                QApplication::processEvents();
            }
        }

        actionPerformed = false;
    }
}

bool Splendor::QtModel::buyReservedCard(Splendor::ResourceCard *c)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.buyReservedCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible d'acheter la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::buyBoardCard(Splendor::ResourceCard *c)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.buyBoardCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible d'acheter la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::reserveCenterCard(Splendor::ResourceCard *c)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.reserveCenterCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible de reserver la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::reserveDrawCard(size_t i)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    bool action = g.reserveDrawCard(i, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible de reserver la carte selectionnée");

    return actionPerformed;
}

bool Splendor::QtModel::takeToken(Splendor::Token t)
{
    if (phase != Phase::Play) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    tokenSelection.push_back(t);

    bool cont = true;
    if (tokenSelection.size() == 2 && tokenSelection[0] == tokenSelection[1]) {
        actionPerformed = g.takeTwoIdenticalToken(tokenSelection[0], p);
    } else if (tokenSelection.size() == 3) {
        actionPerformed = g.takeThreeDifferentToken(tokenSelection[0], tokenSelection[1], tokenSelection[2], p);
    } else {
        cont = false;
    }

    if (cont) {
        tokenSelection.clear();

        if (!actionPerformed)
            promptError("Impossible de prendre les jetons demandés");
    }

    return actionPerformed;
}

bool Splendor::QtModel::returnToken(Splendor::Token t)
{
    if (phase != Phase::Overflow) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    actionPerformed = g.returnToken(t, p);

    if (!actionPerformed)
        promptError("Impossible de rendre le jeton");

    return actionPerformed;
}

bool Splendor::QtModel::chooseNoble(Splendor::NobleCard *c)
{
    if (phase != Phase::Nobles) return false;

    Game &g = getGameInstance();
    Player &p = g.getPlayer(currentPlayer);

    actionPerformed = g.chooseNoble(*c, p);

    if (!actionPerformed)
        promptError("Impossible de choisir ce noble");

    return actionPerformed;
}

void Splendor::QtModel::promptError(std::string s)
{
    QMessageBox message;

    message.setIcon(QMessageBox::Icon::Information);
    message.setText(QString::fromStdString(s));

    message.exec();
}

void Splendor::QtModel::closeEvent(QCloseEvent *event)
{
    this->stopped = true;

    QMainWindow::closeEvent(event);
}
