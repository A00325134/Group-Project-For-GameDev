#include "../Dealer.h"
#include <iostream>

Dealer::Dealer(std::string name)
    : Participant(name)
{
    _standValue = 17;
}

void Dealer::TakeTurn(Deck& deck)
{
    std::cout << "\nDealer's turn...\n";

    while (_hand.GetTotal() < _standValue)
    {
        std::cout << "Dealer hits.\n";
        _hand.AddCard(deck.DealCard());
        std::cout << "Dealer's total is now " << _hand.GetTotal() << ".\n";
    }

    if (_hand.IsBust())
    {
        std::cout << "Dealer went bust!\n";
    }
    else
    {
        std::cout << "Dealer stands.\n";
    }
}
