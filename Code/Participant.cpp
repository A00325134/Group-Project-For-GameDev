#include "Participant.h"

Participant::Participant(std::string name)
{
    _name = name;
}

std::string Participant::GetName() const
{
    return _name;
}

Hand& Participant::GetHand()
{
    return _hand;
}

const Hand& Participant::GetHand() const
{
    return _hand;
}

void Participant::ClearHand()
{
    _hand.Clear();
}
