#pragma once
#include <vector>
#include "Card.h"

class Deck
{
private:
    std::vector<Card> _cards;
    int _nextCard;

public:
    Deck();

    void Reset();
    void Shuffle();
    Card DealCard();
};
