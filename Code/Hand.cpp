#include "../Hand.h"
#include <iostream>

void Hand::AddCard(const Card& card)
{
    _cards.push_back(card);
}

void Hand::Clear()
{
    _cards.clear();
}

int Hand::GetTotal() const
{
    int total = 0;
    int aceCount = 0;

    for (int i = 0; i < (int)_cards.size(); i++)
    {
        total += _cards[i].GetValue();

        if (_cards[i].GetRank() == "Ace")
        {
            aceCount++;
        }
    }

    // An Ace is worth 11 unless that would make the hand bust.
    while (total > 21 && aceCount > 0)
    {
        total -= 10;
        aceCount--;
    }

    return total;
}

int Hand::GetCardCount() const
{
    return (int)_cards.size();
}

bool Hand::IsBust() const
{
    return GetTotal() > 21;
}

bool Hand::IsBlackjack() const
{
    return _cards.size() == 2 && GetTotal() == 21;
}

void Hand::PrintHand(bool hideHoleCard) const
{
    for (int i = 0; i < (int)_cards.size(); i++)
    {
        // The dealer's second card is the hidden hole card.
        if (hideHoleCard && i == (int)_cards.size() - 1)
        {
            std::cout << "[??] ";
        }
        else
        {
            _cards[i].PrintCard();
            std::cout << " ";
        }
    }

    std::cout << std::endl;
}
