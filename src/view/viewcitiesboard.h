#ifndef VIEWCITIESBOARD_H
#define VIEWCITIESBOARD_H

#include "viewboard.h"

class ViewCitiesBoard : public ViewBoard
{
    Q_OBJECT
protected:
    void createNobles() override;
public:
    ViewCitiesBoard(Splendor::Board& board, QWidget* parent=nullptr);
};

#endif // VIEWCITIESBOARD_H
