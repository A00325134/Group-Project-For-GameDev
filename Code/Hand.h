#pragma once
#include <vector>
#include "Card.h"

class Hand
{
private:
    std::vector<Card> _cards;

public:
    void AddCard(const Card& card);
    void Clear();
    int GetTotal() const;
    int GetCardCount() const;
    bool IsBust() const;
    bool IsBlackjack() const;
    void PrintHand(bool hideHoleCard = false) const;
};
