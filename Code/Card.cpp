#include "Card.h"

Card::Card(std::string rank, std::string suit, int value)
{
    _rank = rank;
    _suit = suit;
    _value = value;
}

std::string Card::GetRank() const
{
    return _rank;
}

std::string Card::GetSuit() const
{
    return _suit;
}

int Card::GetValue() const
{
    return _value;
}

void Card::PrintCard() const
{
    std::string shortRank = _rank;
    std::string shortSuit = _suit.substr(0, 1);

    if (_rank == "Ace") shortRank = "A";
    else if (_rank == "Jack") shortRank = "J";
    else if (_rank == "Queen") shortRank = "Q";
    else if (_rank == "King") shortRank = "K";

    // Short ASCII card labels work in standard Windows and Linux consoles.
    std::cout << "[" << shortRank << "-" << shortSuit << "]";
}
