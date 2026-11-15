#pragma once
#include <string>

// Abstract product used by the Factory pattern.
class Level
{
private:
    std::string _name;
    int _minimumBet;
    int _targetChips;
    int _completionBonus;

protected:
    Level(std::string name, int minimumBet, int targetChips, int completionBonus);

public:
    virtual ~Level() {}

    std::string GetName() const;
    int GetMinimumBet() const;
    int GetTargetChips() const;
    int GetCompletionBonus() const;

    virtual void DisplayIntro() const = 0;
};
