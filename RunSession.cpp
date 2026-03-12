#include "RunSession.h"
#include <iostream>

RunSession::RunSession()
{
    money = 2000;
    currentAnte = 1;
    scoringSystem = std::make_unique<ScoringSystem>();
    shopSystem = std::make_unique<ShopSystem>();

    // BattlePhase membutuhkan ScoringSystem untuk beroperasi
    battlePhase = std::make_unique<BattlePhase>(scoringSystem.get());
}

void RunSession::StartGame()
{
    std::cout << "========================================" << "\n";
    std::cout << "   CYBER SURVIVAL CORE LOOP SKELETON    " << "\n";
    std::cout << "========================================" << "\n";

    // CORE LOOP INVARIANT STRUCTURE
    // Terbaca sangat jelas: Selama belum game over -> Bertarung -> Jika menang, buka Toko -> Lanjut
    while (currentAnte <= MAX_WAVES && money > 0)
    {

        bool isWaveCleared = battlePhase->ExecuteBlind(currentAnte, money);

        if (isWaveCleared && currentAnte < MAX_WAVES)
        {
            shopSystem->OpenShop(money);
        }

        currentAnte++;
    }

    std::cout << "\n=== SESSION TERMINATED ===\n";
}