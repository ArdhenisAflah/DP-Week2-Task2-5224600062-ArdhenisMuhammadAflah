#pragma once
#include <vector>
#include "Card.h"

class HandGenerator
{
public:
    std::vector<Card> DealHand(int amount);
};