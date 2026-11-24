#include "Level.h"

Level::Level(std::string name, int minimumBet, int winsRequired, int completionBonus)
{
    _name = name;
    _minimumBet = minimumBet;
    _winsRequired = winsRequired;
    _completionBonus = completionBonus;
}

std::string Level::GetName() const
{
    return _name;
}

int Level::GetMinimumBet() const
{
    return _minimumBet;
}

int Level::GetWinsRequired() const
{
    return _winsRequired;
}

int Level::GetCompletionBonus() const
{
    return _completionBonus;
}
