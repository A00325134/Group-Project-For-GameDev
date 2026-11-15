#include "SaveManager.h"
#include <fstream>
#include <sstream>
#include <string>

bool SaveManager::SaveGame(int chips, int levelNumber, int levelStartChips,
                           int wins, int losses, int pushes, int blackjacks,
                           int rounds, int currentStreak, int bestStreak)
{
    std::ofstream saveFile("blackjack_save.txt");

    if (!saveFile.is_open())
    {
        return false;
    }

    saveFile << "BLACKJACK_SAVE_V3\n";
    saveFile << chips << "\n";
    saveFile << levelNumber << "\n";
    saveFile << levelStartChips << "\n";
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

bool SaveManager::LoadGame(int& chips, int& levelNumber, int& levelStartChips,
                           int& wins, int& losses, int& pushes,
                           int& blackjacks, int& rounds,
                           int& currentStreak, int& bestStreak)
{
    std::ifstream loadFile("blackjack_save.txt");

    if (!loadFile.is_open())
    {
        return false;
    }

    std::string firstLine;
    loadFile >> firstLine;

    if (firstLine == "BLACKJACK_SAVE_V3")
    {
        loadFile >> chips >> levelNumber >> levelStartChips;
        loadFile >> wins >> losses >> pushes >> blackjacks;
        loadFile >> rounds >> currentStreak >> bestStreak;
    }
    else if (firstLine == "BLACKJACK_SAVE_V2")
    {
        // Older saves did not store the bankroll at the start of each table.
        loadFile >> chips >> levelNumber >> wins >> losses;
        loadFile >> pushes >> blackjacks >> rounds;
        loadFile >> currentStreak >> bestStreak;
        levelStartChips = chips;

        // Older versions could mark the campaign complete without playing
        // the VIP table if the bankroll had already passed its fixed target.
        // Let the player enter the VIP table again rather than skipping it.
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
        levelStartChips = chips;
        pushes = 0;
        blackjacks = 0;
        rounds = wins + losses;
        currentStreak = 0;
        bestStreak = 0;
    }

    if (loadFile.fail() || chips < 0 || chips > 1000000000
        || levelNumber < 1 || levelNumber > 4
        || levelStartChips < 0 || levelStartChips > 1000000000
        || wins < 0 || losses < 0 || pushes < 0
        || blackjacks < 0 || rounds < 0
        || currentStreak < 0 || bestStreak < currentStreak)
    {
        loadFile.close();
        return false;
    }

    loadFile.close();
    return true;
}
