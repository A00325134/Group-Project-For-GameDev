#include "Level.h"

Level::Level(std::string name, int minimumBet, int profitTarget, int completionBonus)
{
    _name = name;
    _minimumBet = minimumBet;
    _profitTarget = profitTarget;
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

int Level::GetProfitTarget() const
{
    return _profitTarget;
}

int Level::GetCompletionBonus() const
{
    return _completionBonus;
}
