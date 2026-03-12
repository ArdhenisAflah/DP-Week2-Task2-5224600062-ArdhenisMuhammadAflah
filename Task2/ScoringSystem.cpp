#include "ScoringSystem.h"
#include <iostream>
#include <map>
#include <algorithm>

int ScoringSystem::EvaluateHand(const std::vector<Card> &playedCards)
{
    if (playedCards.empty())
        return 0;

    // Sort  (Descending)
    std::vector<Card> sortedCards = playedCards;
    std::sort(sortedCards.begin(), sortedCards.end(), [](const Card &a, const Card &b)
              {
                  return a.rank > b.rank; // Descending
              });

    //  Detect Pattern flush or straigt first
    bool flush = true;
    for (size_t i = 1; i < sortedCards.size(); i++)
    {
        if (sortedCards[i].suit != sortedCards[0].suit)
            flush = false;
    }

    bool straight = false;
    if (sortedCards.size() >= 5)
    {
        straight = true;
        for (size_t i = 0; i < sortedCards.size() - 1; i++)
        {
            if (sortedCards[i].rank - 1 != sortedCards[i + 1].rank)
                straight = false;
        }
    }

    // Kelompokkan berdasarkan jumlah -> Pair, Trips(three of kind), Quads(four of kind)
    std::map<int, std::vector<Card>> grouped;
    for (const auto &c : sortedCards)
        grouped[c.rank].push_back(c);

    std::vector<Card> quads, trips, pairs;
    // Iterasi mundur agar Pair yang rank-nya lebih tinggi masuk lebih dulu
    for (auto it = grouped.rbegin(); it != grouped.rend(); ++it)
    {
        if (it->second.size() == 4)
            quads = it->second;
        else if (it->second.size() == 3)
            trips = it->second;
        else if (it->second.size() == 2)
            pairs.insert(pairs.end(), it->second.begin(), it->second.end());
    }

    std::string name = "High Card";
    int base = 5, mult = 1;

    // VARIABEL PENAMPUNG KARTU DIHITUNG
    std::vector<Card> scoringCards;

    // 3. Evaluasi Kombinasi & Ekstraksi Scoring Cards
    if (flush && straight && sortedCards.size() >= 5)
    {
        name = "Straight Flush";
        base = 100;
        mult = 8;
        scoringCards = sortedCards; // Semua 5 kartu dihitung
    }
    else if (!quads.empty())
    {
        name = "Four of a Kind";
        base = 60;
        mult = 7;
        scoringCards = quads; // Hanya 4 kartu kembar yang dihitung
    }
    else if (!trips.empty() && !pairs.empty())
    {
        name = "Full House";
        base = 40;
        mult = 4;
        scoringCards = trips;
        scoringCards.insert(scoringCards.end(), pairs.begin(), pairs.end()); // 5 kartu (3+2) dihitung
    }
    else if (flush && sortedCards.size() >= 5)
    {
        name = "Flush";
        base = 35;
        mult = 4;
        scoringCards = sortedCards; // Semua 5 kartu dihitung
    }
    else if (straight && sortedCards.size() >= 5)
    {
        name = "Straight";
        base = 30;
        mult = 4;
        scoringCards = sortedCards; // Semua 5 kartu dihitung
    }
    else if (!trips.empty())
    {
        name = "Three of a Kind";
        base = 30;
        mult = 3;
        scoringCards = trips; // Hanya 3 kartu kembar yang dihitung
    }
    else if (pairs.size() >= 4)
    { // 4 kartu = 2 pasang
        name = "Two Pair";
        base = 20;
        mult = 2;
        scoringCards = pairs; // Hanya 4 kartu (2 pair) yang dihitung
    }
    else if (pairs.size() == 2)
    { // 2 kartu = 1 pasang
        name = "Pair";
        base = 10;
        mult = 2;
        scoringCards = pairs; // Hanya 2 kartu (1 pair) yang dihitung
    }
    else
    {
        name = "High Card";
        base = 5;
        mult = 1;
        scoringCards.push_back(sortedCards.front()); // HANYA 1 KARTU TERTINGGI yang dihitung
    }

    // 4. Hitung Sum HANYA dari Scoring Cards
    int sum = 0;
    std::cout << "   [SYS] Scoring Cards: ";
    for (const auto &c : scoringCards)
    {
        std::cout << c.ToString() << " ";
        sum += (c.rank > 10 ? 10 : c.rank);
    }
    std::cout << "\n";

    int totalDmg = (base + sum) * mult;
    std::cout << "   [CALC] " << name << " -> (Base: " << base << " + Sum: " << sum << ") x " << mult << " Amp\n";
    std::cout << "   [DMG] Total Damage Output: " << totalDmg << "\n";

    return totalDmg;
}