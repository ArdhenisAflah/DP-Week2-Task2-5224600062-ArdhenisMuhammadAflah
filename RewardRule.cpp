#include "RewardRule.h"
#include <iostream>

bool RewardRule::ProcessResult(int finalVirusHP, int &playerMoney)
{
    if (finalVirusHP <= 0)
    {
        playerMoney += 300;
        std::cout << "\n[SUCCESS] VIRUS DELETED. Reward: +$300 | Integrity: $" << playerMoney << "\n";
        return true;
    }
    else
    {
        playerMoney -= finalVirusHP;
        std::cout << "\n[WARNING] DEFENSE FAILED. Penalty: -$" << finalVirusHP << " | Integrity: $" << playerMoney << "\n";
        return false;
    }
}