#include <QApplication>
#include "src/view/viewgame.h"
#include <QDebug>
#include "src/controller.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Splendor::QtController &controller = Splendor::QtController::getInstance();

    controller.launch();

    return app.exec();
}
