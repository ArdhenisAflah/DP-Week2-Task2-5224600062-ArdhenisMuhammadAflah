#include "RunSession.h"
#include <iostream>
#include <sstream>

RunSession::RunSession()
{
    money = 2000;
    currentAnte = 1;
    handGen = std::make_unique<HandGenerator>();
    scoringSystem = std::make_unique<ScoringSystem>();
    rewardRule = std::make_unique<RewardRule>();
    shopSystem = std::make_unique<ShopSystem>();
}

void RunSession::StartGame()
{
    std::cout << "=== CYBER SURVIVAL CORE LOOP ===\n";

    while (currentAnte <= 3 && money > 0)
    {
        int virusHP = 800 * currentAnte;
        int hands = 4;

        std::cout << "\n--- WAVE " << currentAnte << " INITIATED ---\n";

        // INVARIANT 1: BATTLE LOOP
        while (hands > 0 && virusHP > 0)
        {
            std::cout << "VIRUS HP: " << virusHP << " | Attacks: " << hands << "\n";

            // Sub-Invariant A: Generate Input
            std::vector<Card> hand = handGen->DealHand(7);
            std::cout << "[>] Hand: ";
            for (size_t i = 0; i < hand.size(); ++i)
                std::cout << "[" << i << ":" << hand[i].ToString() << "] ";
            std::cout << "\n";

            // Sub-Invariant B: Player Action -> Get Input)
            std::vector<Card> playedCards;
            while (true)
            {
                std::cout << "    Cmd (Select up to 5 idx): ";
                std::string line;
                if (!std::getline(std::cin, line) || line.empty())
                    continue;

                std::stringstream ss(line);
                int idx;
                playedCards.clear();
                bool valid = true;

                while (ss >> idx)
                {
                    if (idx >= 0 && idx < 7 && playedCards.size() < 5)
                        playedCards.push_back(hand[idx]);
                    else
                        valid = false;
                }
                if (valid && !playedCards.empty() && playedCards.size() <= 5)
                    break;
                std::cout << "    [!] Invalid input.\n";
            }
            hands--;

            // Sub-Invariant C: Resolve System
            int damage = scoringSystem->EvaluateHand(playedCards);
            virusHP -= damage;
        }

        // INVARIANT 2: REWARD & EVALUATION
        bool isWin = rewardRule->ProcessResult(virusHP, money);

        // INVARIANT 3: RESTRUCTURE (SHOP)
        if (currentAnte < 3)
        {
            shopSystem->OpenShop(money); // Implementasi shop
        }

        currentAnte++;
    }
    std::cout << "\n=== SESSION TERMINATED ===\n";
}