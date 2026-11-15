#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BlackjackGame.h"
#include "SaveManager.h"

int main()
{
    srand((unsigned int)time(0));

    bool running = true;

    while (running)
    {
        std::cout << "\n+==========================================+\n";
        std::cout << "|       BLACKJACK: ROAD TO THE VIP TABLE   |\n";
        std::cout << "+==========================================+\n";
        std::cout << "|  1. New game                             |\n";
        std::cout << "|  2. Load saved game                      |\n";
        std::cout << "|  3. How to play                          |\n";
        std::cout << "|  4. Quit                                 |\n";
        std::cout << "+------------------------------------------+\n";
        std::cout << "Choose: ";

        int choice = 0;
        if (!(std::cin >> choice))
        {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number from 1 to 4.\n";
            continue;
        }

        if (choice == 1)
        {
            BlackjackGame game;
            game.Start();
        }
        else if (choice == 2)
        {
            int chips = 0;
            int level = 1;
            int wins = 0;
            int losses = 0;
            int pushes = 0;
            int blackjacks = 0;
            int rounds = 0;
            int currentStreak = 0;
            int bestStreak = 0;
            SaveManager saveManager;

            if (saveManager.LoadGame(chips, level, wins, losses, pushes,
                                     blackjacks, rounds, currentStreak, bestStreak))
            {
                std::cout << "Save loaded successfully. Welcome back!\n";
                BlackjackGame game(chips, level, wins, losses, pushes,
                                   blackjacks, rounds, currentStreak, bestStreak);
                game.Start();
            }
            else
            {
                std::cout << "No valid save file was found. Start a new game first.\n";
            }
        }
        else if (choice == 3)
        {
            BlackjackGame::DisplayRules();
        }
        else if (choice == 4)
        {
            running = false;
            std::cout << "Thanks for playing. See you at the tables!\n";
        }
        else
        {
            std::cout << "Invalid choice. Please enter a number from 1 to 4.\n";
        }
    }

    return 0;
}
