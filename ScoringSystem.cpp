#include "ScoringSystem.h"

int ScoringSystem::PlayHand(const std::vector<std::string> &playedCards)
{
    std::cout << "   [SYSTEM] Executing " << playedCards.size() << " data packets: ";
    for (const auto &card : playedCards)
    {
        std::cout << card << " ";
    }
    std::cout << "\n   [SYSTEM] Calculating base damage and executing modifiers...\n";

    // Dummy damage: 150 damage per kartu yang dimainkan 
    return playedCards.size() * 150;
}