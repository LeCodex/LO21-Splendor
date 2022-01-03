#include "qtcontroller.h"

Splendor::QtController::Handler Splendor::QtController::handler;

Splendor::QtController::QtController() : model(nullptr) {}

void Splendor::QtController::initiate() {
    // model = new Splendor::QtModel();
    model = new Splendor::CitiesQtModel();

    model->launch();
}
