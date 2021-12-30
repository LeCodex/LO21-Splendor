#include <QWidget>
#include "controller.h"
#include <QMessageBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QCheckBox>

Splendor::QtController::QtController(QWidget *parent) : QWidget(parent) {}

void Splendor::QtController::initiateGame()
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

    // First we create the four widgets
    for (size_t i = 0; i < 4; i++)
    {
        QWidget *widget = new QWidget;
        QHBoxLayout *line = new QHBoxLayout();
        QLabel *player = new QLabel(QString("Joueur #%1").arg(i));
        QLineEdit *playerInput = new QLineEdit;
        playerInput->setText(QString("Joueur_%1").arg(i));
        QCheckBox *isIa = new QCheckBox("IA");

        line->addWidget(player);
        line->addWidget(playerInput);
        line->addWidget(isIa);

        widget->setLayout(line);

        widgets[i] = widget;
        playerNames[i] = playerInput;

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

    size_t nb = std::stoi(nbJoueurs->text().toStdString());

    // Create an instance of nb player
    Splendor::Game &g = Splendor::Game::createInstance(nb);

    // Add the players
    for (size_t i = 0; i < nb; i++)
        g.addPlayer(playerNames[i]->text().toStdString(), i);

    view = new ViewGame(this);

    // Après avoir initalisé le jeu, l'ajoute a la fenêtre
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(view);

    setLayout(layout);

    showNormal();
}
bool actionPerformed = false;

void Splendor::QtController::playTurn(size_t)
{
    qInfo() << "Waiting for player action...";
    view->setActivePlayer(actual_player);

    // While no action has been performed, just wait for one
    while (!actionPerformed)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    qInfo() << "Action performed!";

    actionPerformed = false;
}
// Verify if the specified player can receive a noble
void Splendor::QtController::nobleVerification(size_t) {}
// Verifiy if the player is too rich
void Splendor::QtController::overflowVerification(size_t) {}

bool Splendor::QtController::buyReservedCard(Splendor::ResourceCard *c)
{
    Game &g = Splendor::Game::getInstance();
    Player &p = g.getPlayer(actual_player);

    try
    {
        bool action = g.buyReservedCard(*c, p);
        actionPerformed = action;

        if (!action)
            promptError("Impossible d'acheter la carte selectionnée");
    }
    catch (char const *c)
    {
        qInfo() << c;
    }

    return actionPerformed;
}
bool Splendor::QtController::buyBoardCard(Splendor::ResourceCard *c)
{
    Game &g = Splendor::Game::getInstance();
    Player &p = g.getPlayer(actual_player);

    bool action = g.buyBoardCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible d'acheter la carte selectionnée");

    return actionPerformed;
}
bool Splendor::QtController::reserveCenterCard(Splendor::ResourceCard *c)
{
    Game &g = Splendor::Game::getInstance();
    Player &p = g.getPlayer(actual_player);

    bool action = g.reserveCenterCard(*c, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible de reserver la carte selectionnée");

    return actionPerformed;
}
bool Splendor::QtController::reserveDrawCard(size_t i)
{
    Game &g = Splendor::Game::getInstance();
    Player &p = g.getPlayer(actual_player);

    bool action = g.reserveDrawCard(i, p);
    actionPerformed = action;

    if (!action)
        promptError("Impossible de reserver la carte selectionnée");

    return actionPerformed;
}
bool Splendor::QtController::takeTwoIdenticalToken()
{
    return false;
}
bool Splendor::QtController::takeThreeDifferentToken()
{
    return false;
}

void Splendor::QtController::promptError(std::string s)
{
    QMessageBox message;

    message.setIcon(QMessageBox::Icon::Information);
    message.setText(QString::fromStdString(s));

    message.exec();
}
