#pragma once
#include <memory>
#include "HandGenerator.h"
#include "ScoringSystem.h"
#include "RewardRule.h"
#include "ShopSystem.h"

class RunSession
{
private:
    int money;
    int currentAnte;

    std::unique_ptr<HandGenerator> handGen;
    std::unique_ptr<ScoringSystem> scoringSystem;
    std::unique_ptr<RewardRule> rewardRule;
    std::unique_ptr<ShopSystem> shopSystem;

public:
    RunSession();
    void StartGame();
};