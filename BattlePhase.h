#pragma once
#include "ScoringSystem.h"

class BattlePhase
{
private:
    ScoringSystem *scoringSystem;

public:
    BattlePhase(ScoringSystem *scoring);
    bool ExecuteBlind(int currentAnte, int &money);
};