#ifndef QTCONTROLLER_H
#define QTCONTROLLER_H

#include "model.h"

namespace Splendor
{
    class QtController
    {
    private:
        QtModel* model;

        QtController();
        ~QtController() { if (model) delete model; }
        friend class Singleton<QtModel>;

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

        QtModel& getModel() const { return *model; }
    };
}

#endif // QTCONTROLLER_H
