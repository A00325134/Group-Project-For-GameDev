#include "Player.h"
#include <iostream>

Player::Player(std::string name, int startingChips)
    : Participant(name)
{
    _chips = startingChips;
    _bet = 0;
}

int Player::GetChips() const
{
    return _chips;
}

int Player::GetBet() const
{
    return _bet;
}

bool Player::PlaceBet(int minimumBet)
{
    if (_chips < minimumBet)
    {
        return false;
    }

    while (true)
    {
        int bet = 0;
        std::cout << "Chips: " << _chips << " | Minimum bet: " << minimumBet << "\n";
        std::cout << "Place your bet: ";

        if (!(std::cin >> bet))
        {
            if (std::cin.eof()) return false;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a whole number.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (bet < minimumBet)
        {
            std::cout << "Your bet must be at least " << minimumBet << ".\n";
        }
        else if (bet > _chips)
        {
            std::cout << "You cannot bet more chips than you have.\n";
        }
        else
        {
            _bet = bet;
            return true;
        }
    }
}

bool Player::CanDoubleDown() const
{
    // Avoid doubling the bet if the player cannot afford the full amount.
    return _hand.GetCardCount() == 2 && _bet > 0
        && _bet <= _chips / 2;
}

bool Player::DoubleBet()
{
    if (!CanDoubleDown())
    {
        return false;
    }

    _bet = _bet * 2;
    return true;
}

void Player::AddChips(int amount)
{
    // Keep the balance inside the range accepted by the save file.
    const int maximumChips = 1000000000;

    if (amount > 0)
    {
        if (_chips > maximumChips - amount)
        {
            _chips = maximumChips;
        }
        else
        {
            _chips += amount;
        }
    }
}

void Player::WinBet()
{
    // The original stake was not removed when the bet was placed.
    AddChips(_bet);
    _bet = 0;
}

void Player::WinBlackjackBet()
{
    // Natural Blackjack pays 3:2. Fractional chips are rounded down.
    // Add the stake plus half the stake, avoiding multiplication overflow.
    AddChips(_bet + (_bet / 2));
    _bet = 0;
}

void Player::LoseBet()
{
    _chips -= _bet;
    _bet = 0;
}

void Player::PushBet()
{
    // A push is a tie. The player's chips do not change.
    _bet = 0;
}

void Player::TakeTurn(Deck& deck)
{
    while (!_hand.IsBust() && _hand.GetTotal() < 21)
    {
        std::cout << "\nYour hand: ";
        _hand.PrintHand();
        std::cout << "Your total: " << _hand.GetTotal() << "\n";
        std::cout << "1. Hit\n";
        std::cout << "2. Stand\n";

        if (CanDoubleDown())
        {
            std::cout << "3. Double down (double your bet, take one card and stand)\n";
        }

        std::cout << "Choose: ";

        int choice = 0;
        if (!(std::cin >> choice))
        {
            if (std::cin.eof())
            {
                std::cout << "\nInput ended. You stand with your current hand.\n";
                break;
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a valid menu number.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (choice == 1)
        {
            _hand.AddCard(deck.DealCard());
            std::cout << "You drew: ";
            _hand.PrintHand();
            std::cout << "Your total is now " << _hand.GetTotal() << ".\n";
        }
        else if (choice == 2)
        {
            std::cout << "You stand.\n";
            break;
        }
        else if (choice == 3 && CanDoubleDown())
        {
            DoubleBet();
            std::cout << "Your bet is now " << _bet << " chips. One final card...\n";
            _hand.AddCard(deck.DealCard());
            std::cout << "You drew: ";
            _hand.PrintHand();
            std::cout << "Your total is now " << _hand.GetTotal() << ".\n";
            break;
        }
        else
        {
            std::cout << "That option is not available. Please choose again.\n";
        }
    }

    if (_hand.IsBust())
    {
        std::cout << "You went bust!\n";
    }
}
