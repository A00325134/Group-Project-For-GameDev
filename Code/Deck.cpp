#include "../Deck.h"
#include <cstdlib>
#include <string>

Deck::Deck()
{
    _nextCard = 0;
    Reset();
}

void Deck::Reset()
{
    _cards.clear();
    _nextCard = 0;

    std::string suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    std::string ranks[13] = {
        "Ace", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "Jack", "Queen", "King"
    };
    int values[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 0; rank < 13; rank++)
        {
            _cards.push_back(Card(ranks[rank], suits[suit], values[rank]));
        }
    }

    Shuffle();
}

void Deck::Shuffle()
{
    // Shuffle from the last card towards the first one.
    for (int i = (int)_cards.size() - 1; i > 0; i--)
    {
        int randomIndex = rand() % (i + 1);
        Card temp = _cards[i];
        _cards[i] = _cards[randomIndex];
        _cards[randomIndex] = temp;
    }

    _nextCard = 0;
}

Card Deck::DealCard()
{
    if (_nextCard >= (int)_cards.size())
    {
        // A fresh shuffle prevents the deck from running out of cards.
        Shuffle();
    }

    Card dealtCard = _cards[_nextCard];
    _nextCard++;
    return dealtCard;
}
