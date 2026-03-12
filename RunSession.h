#pragma once
#include <memory>
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "BattlePhase.h"

class RunSession
{
private:
    int money;
    int currentAnte;
    const int MAX_WAVES = 3;

    //  smart pointer agar easy safe memory
    std::unique_ptr<ScoringSystem> scoringSystem;
    std::unique_ptr<ShopSystem> shopSystem;
    std::unique_ptr<BattlePhase> battlePhase;

public:
    RunSession();
    void StartGame();
};