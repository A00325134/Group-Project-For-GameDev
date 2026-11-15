#include "../Levels.h"
#include <iostream>

BeginnerLevel::BeginnerLevel()
    : Level("Beginner Table", 10, 600, 25)
{
}

void BeginnerLevel::DisplayIntro() const
{
    std::cout << "\n+------------------------------------------+\n";
    std::cout << "|           LEVEL 1: BEGINNER TABLE        |\n";
    std::cout << "+------------------------------------------+\n";
    std::cout << "Minimum bet: 10 chips\n";
    std::cout << "Target: 600 chips\n";
    std::cout << "Table reward: 25 bonus chips\n";
    std::cout << "Get comfortable with Hit, Stand and Double Down.\n";
}

HighRollerLevel::HighRollerLevel()
    : Level("High Roller Table", 25, 850, 50)
{
}

void HighRollerLevel::DisplayIntro() const
{
    std::cout << "\n+------------------------------------------+\n";
    std::cout << "|          LEVEL 2: HIGH ROLLER TABLE      |\n";
    std::cout << "+------------------------------------------+\n";
    std::cout << "Minimum bet: 25 chips\n";
    std::cout << "Target: 850 chips\n";
    std::cout << "Table reward: 50 bonus chips\n";
    std::cout << "Bets are higher now. Play carefully.\n";
}

VIPLevel::VIPLevel()
    : Level("VIP Table", 50, 1200, 100)
{
}

void VIPLevel::DisplayIntro() const
{
    std::cout << "\n+------------------------------------------+\n";
    std::cout << "|              LEVEL 3: VIP TABLE         |\n";
    std::cout << "+------------------------------------------+\n";
    std::cout << "Minimum bet: 50 chips\n";
    std::cout << "Target: 1200 chips\n";
    std::cout << "Table reward: 100 bonus chips\n";
    std::cout << "The final table. Become the Blackjack champion!\n";
}
