# Blackjack class diagram

```mermaid
classDiagram
    class Card {
        -string _rank
        -string _suit
        -int _value
        +GetRank() string
        +GetSuit() string
        +GetValue() int
        +PrintCard() void
    }

    class Deck {
        -vector~Card~ _cards
        -int _nextCard
        +Reset() void
        +Shuffle() void
        +DealCard() Card
    }

    class Hand {
        -vector~Card~ _cards
        +AddCard(Card) void
        +Clear() void
        +GetTotal() int
        +GetCardCount() int
        +IsBust() bool
        +IsBlackjack() bool
        +PrintHand(bool) void
    }

    class Participant {
        <<abstract>>
        #string _name
        #Hand _hand
        +GetName() string
        +GetHand() Hand&
        +ClearHand() void
        +TakeTurn(Deck&) void
    }

    class Player {
        -int _chips
        -int _bet
        +PlaceBet(int) bool
        +CanDoubleDown() bool
        +DoubleBet() bool
        +AddChips(int) void
        +WinBet() void
        +WinBlackjackBet() void
        +LoseBet() void
        +PushBet() void
        +TakeTurn(Deck&) void
    }

    class Dealer {
        -int _standValue
        +TakeTurn(Deck&) void
    }

    class Level {
        <<abstract>>
        -string _name
        -int _minimumBet
        -int _targetChips
        -int _completionBonus
        +GetName() string
        +GetMinimumBet() int
        +GetTargetChips() int
        +GetCompletionBonus() int
        +DisplayIntro() void
    }

    class BeginnerLevel
    class HighRollerLevel
    class VIPLevel

    class LevelFactory {
        +CreateLevel(int) Level*
    }

    class SaveManager {
        +SaveGame(...) bool
        +LoadGame(...) bool
    }

    class BlackjackGame {
        -Player _player
        -Dealer _dealer
        -Deck _deck
        -vector~Participant*~ _participants
        -SaveManager _saveManager
        -int _levelNumber
        -int _wins
        -int _losses
        -int _pushes
        -int _blackjacks
        -int _rounds
        -int _currentStreak
        -int _bestStreak
        -PlayRound(Level&) bool
        -SaveProgress() bool
        -RecordWin() void
        -RecordLoss() void
        +Start() void
        +DisplayRules() void
    }

    Participant <|-- Player
    Participant <|-- Dealer
    Level <|-- BeginnerLevel
    Level <|-- HighRollerLevel
    Level <|-- VIPLevel
    LevelFactory ..> Level : creates
    BlackjackGame *-- Player
    BlackjackGame *-- Dealer
    BlackjackGame *-- Deck
    BlackjackGame *-- SaveManager
    BlackjackGame o-- Participant : non-owning pointers
    Hand *-- Card
    Participant *-- Hand
```

## Design notes

- `Participant` is abstract because `TakeTurn()` is pure virtual. `Player` and `Dealer` override it.
- `Level` is abstract because `DisplayIntro()` is pure virtual. Each concrete level supplies its own introduction and settings.
- `LevelFactory::CreateLevel()` follows the Factory Method example from the lecture notes: it chooses a concrete level and returns it through a base-class pointer.
- `BlackjackGame` owns the `Level*` returned by the factory and deletes it when the level is finished or the game returns to the title screen.
- The `vector<Participant*>` in `BlackjackGame` is non-owning: it only points to `_player` and `_dealer`, which are member objects owned by `BlackjackGame`.
- Cards are stored by value in the deck and hands. This avoids unnecessary `new` and `delete` for ordinary card objects.
- `SaveManager` stores the player's chips, level, round record and streak statistics in a text file.
