#include "../BlackjackGame.h"
#include "LevelFactory.h"
#include <iostream>

BlackjackGame::BlackjackGame(int startingChips, int startingLevel,
                             int wins, int losses, int pushes,
                             int blackjacks, int rounds,
                             int currentStreak, int bestStreak)
    : _player("Player", startingChips), _dealer("Dealer")
{
    _levelNumber = startingLevel;
    _wins = wins;
    _losses = losses;
    _pushes = pushes;
    _blackjacks = blackjacks;
    _rounds = rounds;
    _currentStreak = currentStreak;
    _bestStreak = bestStreak;

    // These pointers refer to objects owned by this BlackjackGame object.
    // The vector does not own them and must not delete them.
    _participants.push_back(&_player);
    _participants.push_back(&_dealer);
}

void BlackjackGame::RecordWin()
{
    _wins++;
    _currentStreak++;

    if (_currentStreak > _bestStreak)
    {
        _bestStreak = _currentStreak;
    }
}

void BlackjackGame::RecordLoss()
{
    _losses++;
    _currentStreak = 0;
}

bool BlackjackGame::SaveProgress()
{
    return _saveManager.SaveGame(_player.GetChips(), _levelNumber,
                                 _wins, _losses, _pushes, _blackjacks,
                                 _rounds, _currentStreak, _bestStreak);
}

bool BlackjackGame::PlayRound(Level& level)
{
    _player.ClearHand();
    _dealer.ClearHand();
    _deck.Reset();

    std::cout << "\n+------------------------------------------+\n";
    std::cout << "|                 NEW ROUND                |\n";
    std::cout << "+------------------------------------------+\n";

    if (!_player.PlaceBet(level.GetMinimumBet()))
    {
        return false;
    }

    // Deal two cards to the player and two to the dealer.
    _player.GetHand().AddCard(_deck.DealCard());
    _dealer.GetHand().AddCard(_deck.DealCard());
    _player.GetHand().AddCard(_deck.DealCard());
    _dealer.GetHand().AddCard(_deck.DealCard());

    std::cout << "\nYour hand: ";
    _player.GetHand().PrintHand();
    std::cout << "Your total: " << _player.GetHand().GetTotal() << "\n";

    std::cout << "Dealer: ";
    _dealer.GetHand().PrintHand(true);

    bool playerBlackjack = _player.GetHand().IsBlackjack();
    bool dealerBlackjack = _dealer.GetHand().IsBlackjack();

    // A natural Blackjack is settled before either participant takes another turn.
    if (playerBlackjack || dealerBlackjack)
    {
        if (playerBlackjack)
        {
            _blackjacks++;
        }

        std::cout << "\nDealer reveals: ";
        _dealer.GetHand().PrintHand();
        std::cout << "Dealer total: " << _dealer.GetHand().GetTotal() << "\n";

        if (playerBlackjack && dealerBlackjack)
        {
            std::cout << "Both have Blackjack. It is a push.\n";
            _player.PushBet();
            _pushes++;
        }
        else if (playerBlackjack)
        {
            std::cout << "NATURAL BLACKJACK! You win at 3:2 odds!\n";
            _player.WinBlackjackBet();
            RecordWin();
        }
        else
        {
            std::cout << "Dealer has Blackjack. You lose this round.\n";
            _player.LoseBet();
            RecordLoss();
        }
    }
    else
    {
        // Polymorphism: Player's TakeTurn() is called through a Participant pointer.
        _participants[0]->TakeTurn(_deck);

        std::cout << "\nDealer reveals: ";
        _dealer.GetHand().PrintHand();
        std::cout << "Dealer total: " << _dealer.GetHand().GetTotal() << "\n";

        if (!_player.GetHand().IsBust())
        {
            // Polymorphism: Dealer's TakeTurn() is called through a Participant pointer.
            _participants[1]->TakeTurn(_deck);
        }
        else
        {
            std::cout << "Dealer does not need to draw because you went bust.\n";
        }

        int playerTotal = _player.GetHand().GetTotal();
        int dealerTotal = _dealer.GetHand().GetTotal();

        std::cout << "\nFinal hands:\n";
        std::cout << "You:    ";
        _player.GetHand().PrintHand();
        std::cout << "Total:  " << playerTotal << "\n";
        std::cout << "Dealer: ";
        _dealer.GetHand().PrintHand();
        std::cout << "Total:  " << dealerTotal << "\n";

        if (_player.GetHand().IsBust())
        {
            std::cout << "You lose this round.\n";
            _player.LoseBet();
            RecordLoss();
        }
        else if (_dealer.GetHand().IsBust())
        {
            std::cout << "Dealer went bust. You win!\n";
            _player.WinBet();
            RecordWin();
        }
        else if (playerTotal > dealerTotal)
        {
            std::cout << "You win this round!\n";
            _player.WinBet();
            RecordWin();
        }
        else if (dealerTotal > playerTotal)
        {
            std::cout << "Dealer wins this round.\n";
            _player.LoseBet();
            RecordLoss();
        }
        else
        {
            std::cout << "It's a tie. Your bet is returned.\n";
            _player.PushBet();
            _pushes++;
        }
    }

    _rounds++;

    std::cout << "\n+---------------- ROUND RESULT -------------+\n";
    std::cout << "Chips: " << _player.GetChips() << "\n";
    std::cout << "Record: " << _wins << " wins | " << _losses << " losses | "
              << _pushes << " pushes\n";
    std::cout << "Current win streak: " << _currentStreak
              << " | Best: " << _bestStreak << "\n";
    std::cout << "+-------------------------------------------+\n";

    if (SaveProgress())
    {
        std::cout << "Progress auto-saved.\n";
    }
    else
    {
        std::cout << "Warning: progress could not be auto-saved.\n";
    }

    return true;
}

void BlackjackGame::PrintSummary() const
{
    std::cout << "\n+==========================================+\n";
    std::cout << "|                GAME SUMMARY              |\n";
    std::cout << "+==========================================+\n";
    std::cout << "Chips:             " << _player.GetChips() << "\n";
    std::cout << "Rounds played:     " << _rounds << "\n";
    std::cout << "Wins:              " << _wins << "\n";
    std::cout << "Losses:            " << _losses << "\n";
    std::cout << "Pushes:            " << _pushes << "\n";
    std::cout << "Blackjacks:        " << _blackjacks << "\n";
    std::cout << "Best win streak:   " << _bestStreak << "\n";

    int decidedRounds = _wins + _losses;
    if (decidedRounds > 0)
    {
        int winRate = (_wins * 100) / decidedRounds;
        std::cout << "Win rate:          " << winRate << "%\n";
    }

    std::cout << "+==========================================+\n";
}

bool BlackjackGame::SaveAndQuit()
{
    if (SaveProgress())
    {
        std::cout << "Progress saved to blackjack_save.txt. Returning to the title screen.\n";
        return true;
    }

    std::cout << "Could not save the game. Check the folder permissions.\n";
    return false;
}

void BlackjackGame::DisplayRules()
{
    std::cout << "\n+==========================================+\n";
    std::cout << "|                HOW TO PLAY               |\n";
    std::cout << "+==========================================+\n";
    std::cout << "Goal: get closer to 21 than the dealer without going over.\n\n";
    std::cout << "Card values:\n";
    std::cout << "  2-10 = face value | J, Q, K = 10 | Ace = 1 or 11\n\n";
    std::cout << "Your choices:\n";
    std::cout << "  Hit         - take another card.\n";
    std::cout << "  Stand       - keep your current total.\n";
    std::cout << "  Double Down - double your bet, take one card, then stand.\n\n";
    std::cout << "Other rules:\n";
    std::cout << "  Dealer draws until reaching 17, then stands.\n";
    std::cout << "  A natural Blackjack (Ace + 10-value card) pays 3:2.\n";
    std::cout << "  A tie is a push and your chips are unchanged.\n";
    std::cout << "  A bust is any total over 21.\n\n";
    std::cout << "Progression:\n";
    std::cout << "  Complete each chip target to unlock the next table.\n";
    std::cout << "  Your progress is automatically saved after each round.\n";
    std::cout << "+==========================================+\n";
}

void BlackjackGame::Start()
{
    std::cout << "\n+==========================================+\n";
    std::cout << "|       BLACKJACK: ROAD TO THE VIP TABLE   |\n";
    std::cout << "+==========================================+\n";

    while (_levelNumber <= 3)
    {
        // The factory creates a level. This game function owns the returned pointer.
        Level* currentLevel = LevelFactory::CreateLevel(_levelNumber);

        if (currentLevel == nullptr)
        {
            break;
        }

        currentLevel->DisplayIntro();

        while (_player.GetChips() < currentLevel->GetTargetChips())
        {
            if (_player.GetChips() < currentLevel->GetMinimumBet())
            {
                break;
            }

            if (!PlayRound(*currentLevel))
            {
                SaveAndQuit();
                delete currentLevel;
                PrintSummary();
                return;
            }

            if (_player.GetChips() >= currentLevel->GetTargetChips())
            {
                break;
            }

            if (_player.GetChips() < currentLevel->GetMinimumBet())
            {
                break;
            }

            int choice = 0;
            bool validChoice = false;

            while (!validChoice)
            {
                std::cout << "\n1. Play another round\n";
                std::cout << "2. Save and return to title screen\n";
                std::cout << "Choose: ";

                if (!(std::cin >> choice))
                {
                    if (std::cin.eof())
                    {
                        SaveAndQuit();
                        delete currentLevel;
                        PrintSummary();
                        return;
                    }

                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1 || choice == 2)
                {
                    validChoice = true;
                }
                else
                {
                    std::cout << "Invalid choice. Please enter 1 or 2.\n";
                }
            }

            if (choice == 2)
            {
                SaveAndQuit();
                delete currentLevel;
                PrintSummary();
                return;
            }
        }

        if (_player.GetChips() < currentLevel->GetMinimumBet())
        {
            std::cout << "\nYou do not have enough chips to place the next bet.\n";
            SaveProgress();
            delete currentLevel;
            PrintSummary();
            std::cout << "Game over! Better luck next time.\n";
            return;
        }

        if (_player.GetChips() >= currentLevel->GetTargetChips())
        {
            int reward = currentLevel->GetCompletionBonus();
            std::cout << "\nCongratulations! You completed the "
                      << currentLevel->GetName() << ".\n";
            std::cout << "Table completion reward: +" << reward << " chips!\n";
            _player.AddChips(reward);

            delete currentLevel;
            _levelNumber++;

            SaveProgress();
        }
    }

    if (_levelNumber > 3)
    {
        std::cout << "\n+==========================================+\n";
        std::cout << "|        YOU ARE THE BLACKJACK CHAMPION!   |\n";
        std::cout << "+==========================================+\n";
    }

    PrintSummary();
}
