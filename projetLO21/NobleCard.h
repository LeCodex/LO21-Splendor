//
// Created by Cléa Bordeau on 02/12/2021.
//
#pragma once
#include "BaseCard.h"

namespace Splendor {
    class NobleCard : public BaseCard
    {
    public:
        NobleCard(int c[], int p) : BaseCard(c, p) {}
    };
}

