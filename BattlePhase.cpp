#include "BattlePhase.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

BattlePhase::BattlePhase(ScoringSystem *scoring) : scoringSystem(scoring) {}

bool BattlePhase::ExecuteBlind(int currentAnte, int &money)
{
    int virusHP = 600 * currentAnte;
    int hands = 4;

    std::cout << "\n--- WAVE " << currentAnte << " INITIATED ---\n";

    while (hands > 0 && virusHP > 0)
    {
        std::cout << "----------------------------------------\n";
        std::cout << "VIRUS HP: " << virusHP << " | Attacks Left: " << hands << "\n";

        // 1. SIMULASI DECK 52 KARTU & DRAW 7 KARTU (Placeholder Logic)
        std::vector<std::string> suits = {"H", "D", "C", "S"};
        std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        std::vector<std::string> deck;

        for (const auto &s : suits)
        {
            for (const auto &r : ranks)
                deck.push_back(r + "-" + s);
        }
        std::random_shuffle(deck.begin(), deck.end());

        std::vector<std::string> hand(deck.begin(), deck.begin() + 7);

        // Menampilkan kartu ke layar
        std::cout << "[>] Hand Buffer: ";
        for (int i = 0; i < 7; ++i)
        {
            std::cout << "[" << i << ":" << hand[i] << "] ";
        }
        std::cout << "\n";

        // 2. INVARIANT: PLAYER ACTION (Memilih maksimal 5 kartu)
        std::vector<std::string> playedCards;
        while (true)
        {
            std::cout << "    Select up to 5 indices (e.g., 0 2 3): ";
            std::string line;
            if (!std::getline(std::cin, line) || line.empty())
                continue;

            std::stringstream ss(line);
            int idx;
            playedCards.clear();
            bool valid = true;

            // Parsing input angka
            while (ss >> idx)
            {
                if (idx >= 0 && idx < 7 && playedCards.size() < 5)
                {
                    playedCards.push_back(hand[idx]);
                }
                else
                {
                    valid = false;
                }
            }

            if (valid && !playedCards.empty() && playedCards.size() <= 5)
                break;
            std::cout << "    [!] Invalid input or exceeded 5 cards. Try again.\n";
        }

        hands--;

        // 3. INVARIANT: SYSTEM RESOLVE
        int damage = scoringSystem->PlayHand(playedCards);
        virusHP -= damage;
        std::cout << "    Virus Threat Reduced! Remaining HP: " << virusHP << "\n";
    }

    // 4. INVARIANT: EVALUATION & STATE UPDATE
    if (virusHP <= 0)
    {
        int reward = 200;
        money += reward;
        std::cout << "\n[SUCCESS] VIRUS DELETED. Reward: +$" << reward << " | Total Integrity: $" << money << "\n";
        return true;
    }
    else
    {
        money -= virusHP;
        std::cout << "\n[WARNING] DEFENSE FAILED. Penalty applied. Remaining Integrity: $" << money << "\n";
        return false;
    }
}