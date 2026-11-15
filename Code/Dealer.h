#pragma once
#include "Participant.h"

class Dealer : public Participant
{
private:
    int _standValue;

public:
    Dealer(std::string name);

    void TakeTurn(Deck& deck) override;
};
