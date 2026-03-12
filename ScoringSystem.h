#pragma once
#include <vector>
#include "Card.h"

class ScoringSystem
{
public:
    int EvaluateHand(const std::vector<Card> &playedCards);
};