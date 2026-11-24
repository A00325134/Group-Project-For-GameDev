#pragma once
#include <vector>
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include "Level.h"
#include "SaveManager.h"
#include "Participant.h"

class BlackjackGame
{
private:
    Player _player;
    Dealer _dealer;
    Deck _deck;
    std::vector<Participant*> _participants; // non-owning pointers to player and dealer
    SaveManager _saveManager;

    int _levelNumber;
    int _tableWins;
    int _wins;
    int _losses;
    int _pushes;
    int _blackjacks;
    int _rounds;
    int _currentStreak;
    int _bestStreak;

    bool PlayRound(Level& level);
    void PrintSummary() const;
    bool SaveAndQuit();
    bool SaveProgress();
    void RecordWin();
    void RecordLoss();

public:
    BlackjackGame(int startingChips = 500, int startingLevel = 1,
                  int wins = 0, int losses = 0, int pushes = 0,
                  int blackjacks = 0, int rounds = 0,
                  int currentStreak = 0, int bestStreak = 0,
                  int tableWins = 0);

    void Start();
    static void DisplayRules();
};
