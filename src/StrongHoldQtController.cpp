#include "controller.h"

Splendor::StrongHoldQtController::Handler Splendor::StrongHoldQtController::handler;

void Splendor::StrongHoldQtController::initiateGame()
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
    Splendor::StrongHoldGame &g = Splendor::StrongHoldGame::createInstance(nb);

    // Add the players
    for (size_t i = 0; i < nb; i++)
        g.addPlayer(playerNames[i]->text().toStdString(), AI[i]->checkState(), i);

    view = new ViewGame(&g, this);

    // Changer la couleur de fond
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::darkCyan);
    view ->setAutoFillBackground(true);
    view->setPalette(pal);
    view->show();

    // Après avoir initalisé le jeu, l'ajoute a la fenêtre
    setCentralWidget(view);

    show();
}
