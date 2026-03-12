#include "HandGenerator.h"
#include <algorithm>

std::vector<Card> HandGenerator::DealHand(int amount)
{
    std::vector<Card> deck;
    for (int s = 0; s < 4; s++)
    {
        for (int r = 2; r <= 14; r++)
        {
            deck.push_back({(Suit)s, r});
        }
    }
    std::random_shuffle(deck.begin(), deck.end());

    std::vector<Card> hand(deck.begin(), deck.begin() + amount);
    return hand;
}