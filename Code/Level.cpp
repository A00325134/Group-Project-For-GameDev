#include "../Level.h"

Level::Level(std::string name, int minimumBet, int targetChips, int completionBonus)
{
    _name = name;
    _minimumBet = minimumBet;
    _targetChips = targetChips;
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

int Level::GetTargetChips() const
{
    return _targetChips;
}

int Level::GetCompletionBonus() const
{
    return _completionBonus;
}
