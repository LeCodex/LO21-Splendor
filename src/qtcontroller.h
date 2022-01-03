#ifndef QTCONTROLLER_H
#define QTCONTROLLER_H

#include "model.h"

namespace Splendor
{
    class QtController
    {
    private:
        enum Extension{
            VANILLA,
            CITIES
        };


        QLineEdit *playerNames[4];
        QCheckBox *AI[4];
        size_t nb;

        QtModel* model;

        QtController();
        ~QtController() { if (model) delete model; }

        struct Handler
        {
            QtController *instance;
            Handler() : instance(nullptr) {}
            ~Handler() { delete instance; }
        };

        static Handler handler;
    public:
        QtController(const QtController&) = delete;
        QtController& operator=(const QtController&) = delete;

        static QtController &getInstance()
        {
            if (handler.instance == nullptr)
                handler.instance = new QtController();
            return *handler.instance;
        }
        void initiate();

        auto getPlayerNames() const { return playerNames; }
        auto getAi() const { return AI; }
        auto getNb() const { return nb; }

        QtModel& getModel() const { return *model; }
    };
}

#endif // QTCONTROLLER_H
