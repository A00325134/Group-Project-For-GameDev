#pragma once

class SaveManager
{
public:
    bool SaveGame(int chips, int levelNumber, int wins, int losses,
                  int pushes, int blackjacks, int rounds,
                  int currentStreak, int bestStreak);

    bool LoadGame(int& chips, int& levelNumber, int& wins, int& losses,
                  int& pushes, int& blackjacks, int& rounds,
                  int& currentStreak, int& bestStreak);
};
