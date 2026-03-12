#pragma once
#include <string>

enum Suit
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

struct Card
{
    Suit suit;
    int rank; // 2-14 (11=J, 12=Q, 13=K, 14=A)

    std::string ToString() const
    {
        std::string rStr = (rank <= 10) ? std::to_string(rank) : (rank == 11) ? "J"
                                                             : (rank == 12)   ? "Q"
                                                             : (rank == 13)   ? "K"
                                                                              : "A";
        std::string sStr = (suit == HEARTS) ? "H" : (suit == DIAMONDS) ? "D"
                                                : (suit == CLUBS)      ? "C"
                                                                       : "S";
        return rStr + "-" + sStr;
    }
};