#include "RunSession.h"
#include <ctime>
#include <cstdlib>

int main()
{
    std::srand(std::time(0)); // Inisialisasi seed random
    RunSession gameSession;
    gameSession.StartGame();
    return 0;
}