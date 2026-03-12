#include "ScoringSystem.h"
#include <iostream>
#include <map>

int ScoringSystem::EvaluateHand(const std::vector<Card> &playedCards)
{
    if (playedCards.empty())
        return 0;

    bool flush = true;
    for (size_t i = 1; i < playedCards.size(); i++)
    {
        if (playedCards[i].suit != playedCards[0].suit)
            flush = false;
    }

    std::map<int, int> counts;
    for (const auto &c : playedCards)
        counts[c.rank]++;

    int pairs = 0;
    bool three = false;
    for (const auto &kv : counts)
    {
        if (kv.second == 2)
            pairs++;
        if (kv.second == 3)
            three = true;
    }

    std::string name = "High Card";
    int base = 10, mult = 1;

    if (flush && playedCards.size() >= 5)
    {
        name = "Flush";
        base = 40;
        mult = 4;
    }
    else if (three && pairs)
    {
        name = "Full House";
        base = 40;
        mult = 4;
    }
    else if (three)
    {
        name = "Three of a Kind";
        base = 30;
        mult = 3;
    }
    else if (pairs == 2)
    {
        name = "Two Pair";
        base = 20;
        mult = 2;
    }
    else if (pairs == 1)
    {
        name = "Pair";
        base = 10;
        mult = 2;
    }

    int sum = 0;
    for (const auto &c : playedCards)
        sum += (c.rank > 10 ? 10 : c.rank);

    int totalDmg = (base + sum) * mult;
    std::cout << "   [CALC] " << name << " -> (Base: " << base << " + Sum: " << sum << ") x " << mult << " Amp\n";
    std::cout << "   [DMG] Total Damage Output: " << totalDmg << "\n";
    return totalDmg;
}