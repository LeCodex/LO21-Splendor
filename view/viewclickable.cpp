#include "viewclickable.h"

ViewClickable::ViewClickable(QWidget* parent): QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
}
