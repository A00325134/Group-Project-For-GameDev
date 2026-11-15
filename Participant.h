#pragma once
#include <string>
#include "Hand.h"
#include "Deck.h"

// Abstract base class shared by the human player and the dealer.
class Participant
{
protected:
    std::string _name;
    Hand _hand;

public:
    Participant(std::string name);
    virtual ~Participant() {}

    std::string GetName() const;
    Hand& GetHand();
    const Hand& GetHand() const;
    void ClearHand();

    virtual void TakeTurn(Deck& deck) = 0;
};
