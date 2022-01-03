#include <QApplication>
#include "src/view/viewgame.h"
#include <QDebug>
#include "src/qtcontroller.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Splendor::QtController &controller = Splendor::QtController::getInstance();
    controller.initiate();

    return app.exec();
}
