#pragma once
#include <iostream>
#include <vector>
#include <string>

class ScoringSystem {
public:
    // Menerima input array berisi kartu yang dipilih pemain
    int PlayHand(const std::vector<std::string>& playedCards);
};