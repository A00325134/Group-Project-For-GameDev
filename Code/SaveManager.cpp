#include "SaveManager.h"
#include <fstream>
#include <sstream>
#include <string>

bool SaveManager::SaveGame(int chips, int levelNumber, int tableWins,
                           int wins, int losses, int pushes, int blackjacks,
                           int rounds, int currentStreak, int bestStreak)
{
    std::ofstream saveFile("blackjack_save.txt");

    if (!saveFile.is_open())
    {
        return false;
    }

    // V4 stores wins earned at the current table separately from lifetime wins.
    saveFile << "BLACKJACK_SAVE_V4\n";
    saveFile << chips << "\n";
    saveFile << levelNumber << "\n";
    saveFile << tableWins << "\n";
    saveFile << wins << "\n";
    saveFile << losses << "\n";
    saveFile << pushes << "\n";
    saveFile << blackjacks << "\n";
    saveFile << rounds << "\n";
    saveFile << currentStreak << "\n";
    saveFile << bestStreak << "\n";

    saveFile.close();
    return !saveFile.fail();
}

bool SaveManager::LoadGame(int& chips, int& levelNumber, int& tableWins,
                           int& wins, int& losses, int& pushes,
                           int& blackjacks, int& rounds,
                           int& currentStreak, int& bestStreak)
{
    std::ifstream loadFile("blackjack_save.txt");

    if (!loadFile.is_open())
    {
        return false;
    }

    tableWins = 0;
    std::string firstLine;
    loadFile >> firstLine;

    if (firstLine == "BLACKJACK_SAVE_V4")
    {
        loadFile >> chips >> levelNumber >> tableWins;
        loadFile >> wins >> losses >> pushes >> blackjacks;
        loadFile >> rounds >> currentStreak >> bestStreak;
    }
    else if (firstLine == "BLACKJACK_SAVE_V3")
    {
        // V3 used chip profit targets and stored the starting balance for a table.
        // It did not record wins at each table, so start the current table at 0/3.
        int oldLevelStartChips = 0;
        loadFile >> chips >> levelNumber >> oldLevelStartChips;
        loadFile >> wins >> losses >> pushes >> blackjacks;
        loadFile >> rounds >> currentStreak >> bestStreak;

        if (levelNumber == 4)
        {
            // Older builds could skip the VIP table. Re-enter it under the new rules.
            levelNumber = 3;
        }
    }
    else if (firstLine == "BLACKJACK_SAVE_V2")
    {
        loadFile >> chips >> levelNumber >> wins >> losses;
        loadFile >> pushes >> blackjacks >> rounds;
        loadFile >> currentStreak >> bestStreak;

        if (levelNumber == 4)
        {
            levelNumber = 3;
        }
    }
    else
    {
        // Also accept the original four-number save format.
        std::stringstream numberLine(firstLine);
        if (!(numberLine >> chips))
        {
            loadFile.close();
            return false;
        }

        loadFile >> levelNumber >> wins >> losses;
        pushes = 0;
        blackjacks = 0;
        rounds = wins + losses;
        currentStreak = 0;
        bestStreak = 0;
    }

    if (loadFile.fail() || chips < 0 || chips > 1000000000
        || levelNumber < 1 || levelNumber > 4
        || tableWins < 0 || tableWins > 3
        || wins < 0 || tableWins > wins || losses < 0 || pushes < 0
        || blackjacks < 0 || rounds < 0
        || currentStreak < 0 || bestStreak < currentStreak)
    {
        loadFile.close();
        return false;
    }

    loadFile.close();
    return true;
}
