#pragma once
#include "Participant.h"

class Player : public Participant
{
private:
    int _chips;
    int _bet;

public:
    Player(std::string name, int startingChips);

    int GetChips() const;
    int GetBet() const;
    bool PlaceBet(int minimumBet);
    bool CanDoubleDown() const;
    bool DoubleBet();
    void AddChips(int amount);
    void WinBet();
    void WinBlackjackBet();
    void LoseBet();
    void PushBet();
    void TakeTurn(Deck& deck) override;
};
